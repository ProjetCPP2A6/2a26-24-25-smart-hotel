#include "mainservice.h"
#include "ui_mainservice.h"
#include <QMessageBox>
#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QPageSize>
#include <QDateTime>
#include <QStandardItemModel>
#include <QSqlQueryModel>

mainservice::mainservice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainservice),
    model(new QSqlQueryModel(this))
{
    ui->setupUi(this);

    ui->lineEdit_id->setValidator(new QIntValidator(1, 10000000, this));
    ui->lineEdit_idSP->setValidator(new QIntValidator(1, 10000000, this));
    ui->lineEdit_id_ed->setValidator(new QIntValidator(1, 10000000, this));
    ui->lineEdit_sr->setValidator(new QIntValidator(1, 10000000, this));

    // Validator for Nom and Prenom - alphabetic characters only
    QRegularExpression alphabetRegex("^[a-zA-Z]+$");
    ui->lineEdit_nom->setValidator(new QRegularExpressionValidator(alphabetRegex, this));
    ui->lineEdit_prenom->setValidator(new QRegularExpressionValidator(alphabetRegex, this));

    QStringList positions = {"Manager", "Developer", "Designer", "HR", "Sales"};
    ui->comboBox_poste->addItems(positions);
    ui->comboBox_poste_ed->addItems(positions);

    // Validator for Salaire - double values only with optional decimals
    ui->lineEdit_salaire->setValidator(new QDoubleValidator(0, 1000000, 2, this));
    ui->lineEdit_salaire_ed->setValidator(new QDoubleValidator(0, 1000000, 2, this));

    ui->chatDisplay->setReadOnly(true);
    connect(ui->sendButton, &QPushButton::clicked, this, &mainservice::onSendMessage);
    connect(ui->inputField, &QLineEdit::returnPressed, ui->sendButton, &QPushButton::click);
    connect(ui->pushButton, &QPushButton::clicked, this, &mainservice::onLoginButtonClicked);
    connect(ui->pushButton_analysis, &QPushButton::clicked, this, &mainservice::on_pushButton_analysis_clicked);

    // Populate the combo box with static values or dynamic data
    ui->comboBox_poste_2->addItem("Manager");
    ui->comboBox_poste_2->addItem("Developer");
    ui->comboBox_poste_2->addItem("HR");

    // Populate comboBox dynamically from the database
    QSqlQuery query;
    if (query.exec("SELECT DISTINCT poste FROM Employes")) {
        while (query.next()) {
            ui->comboBox_poste->addItem(query.value(0).toString());
        }
    } else {
        qDebug() << "Failed to fetch postes:" << query.lastError().text();
    }


    // Set up QTableView model to display Attendance logs using QSqlQueryModel
    QString attendanceQuery = "SELECT id_Attendance, id_Employe, timestamp, status FROM Attendance ORDER BY timestamp DESC";
    model->setQuery(attendanceQuery);

    if (model->lastError().isValid()) {
        qDebug() << "Query Error:" << model->lastError().text();
    }

    ui->tableView_Logs->setModel(model);

    // Configure QTableView
    ui->tableView_Logs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_Logs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_Logs->resizeColumnsToContents();
    ui->tableView_Logs->horizontalHeader()->setStretchLastSection(true);

    setupSerial();

    connect(serialPort, &QSerialPort::readyRead, this, &mainservice::readSerialData);


}


mainservice::~mainservice()
{
    delete ui;

}



void mainservice::setupSerial()
{
    serialPort->setPortName("COM4"); // Replace with your Arduino's COM port
    serialPort->setBaudRate(QSerialPort::Baud9600);

    if (!serialPort->open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Failed to open serial port.");
    }
}

void mainservice::readSerialData()
{
    QByteArray data = serialPort->readAll();
    QString id = QString::fromUtf8(data).trimmed();
    ui->lineEdit_ID->setText(id);
    handleAttendance(id);
}

void mainservice::processInput()
{
    QString id = ui->lineEdit_ID->text().trimmed();
    handleAttendance(id);
}

void mainservice::handleAttendance(const QString &id)
{
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid ID.");
        return;
    }

    QSqlQuery query;

    // Step 1: Check if the employee exists
    query.prepare("SELECT nom, prenom FROM Employes WHERE id_Employe = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error executing employee check:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to check employee.");
        return;
    }

    if (!query.next()) {
        ui->label_EmployeeInfo->setText("Employee not found.");
        qDebug() << "Employee ID not found:" << id;
        return;
    }

    QString name = query.value(0).toString() + " " + query.value(1).toString();

    // Step 2: Fetch the latest attendance record for this employee
    // Correct the query to use subquery with ROWNUM for Oracle compatibility
    QString latestAttendanceQuery = "SELECT timestamp, status "
                                    "FROM (SELECT timestamp, status "
                                    "      FROM Attendance "
                                    "      WHERE id_Employe = :id "
                                    "      ORDER BY timestamp DESC) "
                                    "WHERE ROWNUM = 1";

    query.prepare(latestAttendanceQuery);
    query.bindValue(":id", id);

    QDateTime lastTimestamp;
    QString lastStatus;
    QDateTime currentTimestamp = QDateTime::currentDateTime();
    QString newStatus;

    if (query.exec() && query.next()) {
        lastTimestamp = query.value(0).toDateTime();
        lastStatus = query.value(1).toString();

        // Debugging: Log last timestamp and status
        qDebug() << "Last Timestamp:" << lastTimestamp.toString("yyyy-MM-dd HH:mm:ss")
                 << "Last Status:" << lastStatus;

        if (lastStatus == "Left") {
            if (lastTimestamp.addSecs(120) <= currentTimestamp) { // 2 minutes = 120 seconds
                // Allow entry if 2 minutes have passed
                newStatus = "Entered";
            } else {
                // Block re-entry if less than 2 minutes
                QMessageBox::warning(this, "Error", "You need to wait 2 minutes before re-entering.");
                qDebug() << "Re-entry blocked for employee ID:" << id;
                return;
            }
        } else if (lastStatus == "Entered") {
            // Allow the employee to exit
            newStatus = "Left";
        }
    } else {
        // First-time entry
        newStatus = "Entered";
    }

    // Step 3: Insert the new attendance record
    query.prepare("INSERT INTO Attendance (id_Employe, timestamp, status) VALUES (:id, :timestamp, :status)");
    query.bindValue(":id", id);
    query.bindValue(":timestamp", currentTimestamp);
    query.bindValue(":status", newStatus);

    if (!query.exec()) {
        qDebug() << "Failed to insert log into Attendance table:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to log attendance.");
        return;
    }

    // Step 4: Display the information in label_EmployeeInfo
    QString info;

    if (newStatus == "Entered") {
        info = QString("Welcome %1\nEntered at: %2")
        .arg(name)
            .arg(currentTimestamp.toString("yyyy-MM-dd HH:mm:ss"));
    } else if (newStatus == "Left") {
        info = QString("Goodbye %1\nEntered at: %2\nLeft at: %3")
        .arg(name)
            .arg(lastTimestamp.toString("yyyy-MM-dd HH:mm:ss"))
            .arg(currentTimestamp.toString("yyyy-MM-dd HH:mm:ss"));
    }

    ui->label_EmployeeInfo->setText(info);

    // Debugging: Show final displayed message
    qDebug() << "Displayed info:" << info;

    // Step 5: Refresh the model to update the QTableView
    QString updatedAttendanceQuery = "SELECT id_Attendance, id_Employe, timestamp, status "
                                     "FROM Attendance "
                                     "ORDER BY timestamp DESC";

    model->setQuery(updatedAttendanceQuery);

    if (model->lastError().isValid()) {
        qDebug() << "Query Error after refresh:" << model->lastError().text();
    }

    // Optionally, you can resize columns again if necessary
    ui->tableView_Logs->resizeColumnsToContents();
}


void mainservice::on_pushButton_analysis_clicked() {
    // Call the populateStatistics function and pass the table view
    service->populateStatistics(ui->tableView);
}
void mainservice::populateStatistics(QTableView *tableView) {
    // Prepare a query to calculate the average salary grouped by `poste`
    QSqlQuery query("SELECT poste, COUNT(*) AS employee_count, AVG(salaire) AS avg_salary FROM Employes GROUP BY poste");

    // Check for query errors
    if (query.lastError().isValid()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    // Create a model to store the results
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"Poste", "Employee Count", "Average Salary"});

    // Fetch results and populate the model
    int row = 0;
    while (query.next()) {
        QString poste = query.value("poste").toString();
        int employeeCount = query.value("employee_count").toInt();
        double avgSalary = query.value("avg_salary").toDouble();

        model->setItem(row, 0, new QStandardItem(poste));
        model->setItem(row, 1, new QStandardItem(QString::number(employeeCount)));
        model->setItem(row, 2, new QStandardItem(QString::number(avgSalary, 'f', 2)));
        row++;
    }

    // Set the model to the table view
    tableView->setModel(model);
}

void mainservice::onSendMessage() {
    QString userInput = ui->inputField->text();

    if (userInput.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a message.");
        return;
    }

    // Append user message to chat display
    ui->chatDisplay->append("You: " + userInput);

    // Process the user's input
    QString response;
    if (userInput.toLower().contains("information")) {
        response = "Please provide your employee ID.";
    } else if (userInput.toInt() > 0) { // Assume user entered an ID
        int id = userInput.toInt();
        QSqlQuery query;
        query.prepare("SELECT nom, prenom, poste, date_embauche, salaire FROM Employes WHERE id_Employe = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {
            QString name = query.value(0).toString();
            QString surname = query.value(1).toString();
            QString poste = query.value(2).toString();
            QString date = query.value(3).toDate().toString();
            double salary = query.value(4).toDouble();

            response = QString("Employee Found:\nName: %1 %2\nPoste: %3\nDate of Hire: %4\nSalary: %5")
                           .arg(name)
                           .arg(surname)
                           .arg(poste)
                           .arg(date)
                           .arg(salary);
        } else {
            response = "No employee found with the given ID.";
        }
    } else if (userInput.toLower().contains("salary")) {
        response = "Please provide your ID to check your salary.";
    } else {
        response = "Sorry, I didn't understand that. You can ask for employee information or your salary.";
    }

    // Append bot response to chat display
    ui->chatDisplay->append("Bot: " + response);

    // Clear input field
    ui->inputField->clear();
}
void mainservice::on_pushButton_ajouter_clicked() {
    // Get input values from the UI
    int id = ui->lineEdit_id->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString poste = ui->comboBox_poste->currentText();
    QDate date_embauche = ui->dateEdit_embauche->date();
    double salaire = ui->lineEdit_salaire->text().toDouble();

    if (id <= 0 || nom.isEmpty() || prenom.isEmpty() || poste.isEmpty() || salaire <= 0.0) {
        QMessageBox::warning(this, "Error", "Please fill in all fields with valid data.");
        return;
    }

    employe newEmploye(id, nom, prenom, poste, date_embauche, salaire);

    if (newEmploye.addEmployeToDB()) {
        QMessageBox::information(this, "Success", "Employe added successfully!");
        // Clear fields after successful addition
        ui->lineEdit_id->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_prenom->clear();
        ui->comboBox_poste->setCurrentIndex(0);
        ui->dateEdit_embauche->clear();
        ui->lineEdit_salaire->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add employe. Check for duplicate ID or database errors.");
    }
}


void mainservice::on_pushButton_supprimer_clicked() {

    int id_employe = ui->lineEdit_idSP->text().toInt();


    employe employeToDelete(id_employe, "", "", "", QDate(), 0);

    if (employeToDelete.deleteEmployeFromDB(id_employe)) {
        QMessageBox::information(this, "Success", "Employe deleted successfully.");


        ui->lineEdit_idSP->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete employe. Check the ID.");
    }
}


void mainservice::on_pushButton_afficher_clicked() {

    // Clear the table to prepare for new data
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Get the id_Employe from the line edit
    int id_employe = ui->lineEdit_sr->text().toInt();
    qDebug() << "id_Employe:" << id_employe;  // Debugging: Log the id_employe value

    // Get the selected poste from the combo box
    QString poste = ui->comboBox_poste_2->currentText();
    qDebug() << "Selected poste:" << poste;  // Debugging: Log the selected poste value

    // Validate id_employe or poste to ensure at least one is provided
    if (id_employe <= 0 && poste.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a valid employe ID or select a poste.");
        return;
    }

    QSqlQuery query;
    QString queryStr = "SELECT id_Employe, nom, prenom, poste, date_embauche, salaire FROM Employes WHERE 1=1";

    // Add condition for id_Employe if provided
    if (id_employe > 0) {
        queryStr += " AND id_Employe = :id_Employe";
    }

    // Add condition for poste if selected (not empty)
    if (!poste.isEmpty()) {
        queryStr += " AND poste = :poste";
    }

    // Debugging: Log the query string
    qDebug() << "Executing query:" << queryStr;

    // Prepare the query
    query.prepare(queryStr);

    // Bind the values if they are set
    if (id_employe > 0) {
        query.bindValue(":id_Employe", id_employe);
    }
    if (!poste.isEmpty()) {
        query.bindValue(":poste", poste);
    }

    // Execute the query
    if (query.exec()) {
        bool found = false;

        // Process the result
        while (query.next()) {
            found = true;

            // Insert row in the tableWidget
            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);

            // Set the data into tableWidget
            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(query.value(0).toString()));  // id_Employe
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(query.value(1).toString()));  // nom
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(query.value(2).toString()));  // prenom
            ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(query.value(3).toString()));  // poste
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(query.value(4).toString()));  // date_embauche
            ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(query.value(5).toString()));  // salaire
        }

        // If no rows are found, show a warning
        if (!found) {
            QMessageBox::warning(this, "No Results", "No employe found with the given criteria.");
        }
    } else {
        qDebug() << "Query execution failed:" << query.lastError().text();
        QMessageBox::warning(this, "Error", "Failed to execute query.");
    }
}






void mainservice::on_pushButton_edit_clicked() {
    int id_employe = ui->lineEdit_id_ed->text().toInt();
    QString newPoste = ui->comboBox_poste_ed->currentText();
    double newSalaire = ui->lineEdit_salaire_ed->text().toDouble();

    // Check if the employee ID exists in the database
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT poste, salaire FROM Employes WHERE id_Employe = :id_Employe");
    checkQuery.bindValue(":id_Employe", id_employe);

    if (!checkQuery.exec()) {
        QMessageBox::warning(this, "Error", "Failed to check employee ID. Please try again.");
        return;
    }

    if (!checkQuery.next()) {
        QMessageBox::warning(this, "Error", "Employee ID does not exist in the database.");
        return;
    }

    // Retrieve current employee data
    QString currentPoste = checkQuery.value("poste").toString();
    double currentSalaire = checkQuery.value("salaire").toDouble();

    // Check if there are any changes
    if (newPoste == currentPoste && newSalaire == currentSalaire) {
        QMessageBox::information(this, "No Changes", "No changes were made to the employee data.");
        return;
    }

    // Proceed with the update if changes are detected
    QString nom = ""; // Assuming you still need to gather these values from somewhere else
    QString prenom = "";
    QDate date_embauche = QDate();
    employe employeToEdit(id_employe, nom, prenom, newPoste, date_embauche, newSalaire);

    if (employeToEdit.editEmployeInDB(id_employe, nom, prenom, newPoste, date_embauche, newSalaire)) {
        QMessageBox::information(this, "Success", "Employee updated successfully.");
        ui->lineEdit_id_ed->clear();
        ui->comboBox_poste_ed->setCurrentIndex(0);
        ui->lineEdit_salaire_ed->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update employee. Check the ID.");
    }
}

// New slot to fetch current employee data
void mainservice::on_lineEdit_id_ed_editingFinished() {
    int id_employe = ui->lineEdit_id_ed->text().toInt();

    // Ensure the ID is valid
    if (id_employe <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid employee ID.");
        return;
    }

    // Query to fetch current employee data
    QSqlQuery query;
    query.prepare("SELECT poste, salaire FROM Employes WHERE id_Employe = :id_Employe");
    query.bindValue(":id_Employe", id_employe);

    if (!query.exec()) {
        QMessageBox::warning(this, "Error", "Failed to fetch employee data. Please try again.");
        return;
    }

    if (!query.next()) {
        QMessageBox::warning(this, "Error", "Employee ID does not exist in the database.");
        return;
    }

    // Retrieve current data
    QString currentPoste = query.value("poste").toString();
    double currentSalaire = query.value("salaire").toDouble();

    // Populate the UI elements with current data
    ui->comboBox_poste_ed->setCurrentText(currentPoste);
    ui->lineEdit_salaire_ed->setText(QString::number(currentSalaire));
}





void mainservice::on_pushButton_afficher_tous_clicked()
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0); // Clear existing content

    // Ensure the database is connected
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "Database Error", "Database is not connected!");
        return;
    }

    // Query to get all employees
    QString queryString = "SELECT id_Employe, nom, prenom, poste, date_embauche, salaire FROM Employes";
    qDebug() << "Executing query:" << queryString;

    QSqlQuery query;
    if (!query.exec(queryString)) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        QMessageBox::warning(this, "Error", "Failed to execute query: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        int rowCount = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(rowCount);

        // Populate the table with employee data
        ui->tableWidget_2->setItem(rowCount, 0, new QTableWidgetItem(query.value(0).toString())); // id_Employe
        ui->tableWidget_2->setItem(rowCount, 1, new QTableWidgetItem(query.value(1).toString())); // nom
        ui->tableWidget_2->setItem(rowCount, 2, new QTableWidgetItem(query.value(2).toString())); // prenom
        ui->tableWidget_2->setItem(rowCount, 3, new QTableWidgetItem(query.value(3).toString())); // poste
        ui->tableWidget_2->setItem(rowCount, 4, new QTableWidgetItem(query.value(4).toString())); // date_embauche
        ui->tableWidget_2->setItem(rowCount, 5, new QTableWidgetItem(query.value(5).toString())); // salaire
    }

    // Notify the user about the number of records displayed
    if (ui->tableWidget_2->rowCount() > 0) {
        QMessageBox::information(this, "Success", "All employees displayed successfully!");
    } else {
        QMessageBox::information(this, "Information", "No employees found in the database.");
    }
}
void mainservice::on_pushButton_pdf_clicked() {
    // Ask for file location
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");

    if (fileName.isEmpty()) {
        return; // User cancelled the file dialog
    }

    // Create a PDF writer object
    QPdfWriter writer(fileName);
    QPageSize pageSize(QPageSize::A4);  // Correct way to set A4 size
    writer.setPageSize(pageSize);
    writer.setResolution(300);  // Set the resolution of the PDF

    // Create a QPainter to write on the PDF
    QPainter painter;
    if (!painter.begin(&writer)) {
        QMessageBox::warning(this, "Error", "Failed to create PDF.");
        return;
    }

    // Set font for the PDF content
    QFont font;
    font.setPointSize(12);
    painter.setFont(font);

    // Set the page margins
    int margin = 30;
    int yPosition = margin;  // Start from the top of the page

    // Draw the title of the PDF
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(margin, yPosition, "Employee Report");

    // Adjust position for the content
    yPosition += 30;  // Move down after the title

    // Draw a horizontal line under the title for separation
    painter.drawLine(margin, yPosition, writer.width() - margin, yPosition);
    yPosition += 10;  // Space after the line

    // Draw column headers with a background color
    QBrush headerBrush(QColor(200, 200, 200)); // Light gray background for headers
    painter.setBrush(headerBrush);
    painter.setPen(Qt::black);
    painter.drawRect(margin, yPosition - 20, 100, 30); // ID
    painter.drawRect(margin + 100, yPosition - 20, 200, 30); // Name
    painter.drawRect(margin + 300, yPosition - 20, 100, 30); // Position
    painter.drawRect(margin + 400, yPosition - 20, 120, 30); // Hire Date
    painter.drawRect(margin + 520, yPosition - 20, 80, 30); // Salary

    // Set font for headers (bold)
    painter.setFont(QFont("Arial", 12, QFont::Bold));

    // Draw the header text
    painter.drawText(margin + 10, yPosition, "ID");
    painter.drawText(margin + 110, yPosition, "Name");
    painter.drawText(margin + 310, yPosition, "Position");
    painter.drawText(margin + 410, yPosition, "Hire Date");
    painter.drawText(margin + 530, yPosition, "Salary");

    // Adjust yPosition for the next row
    yPosition += 30;  // Move down after headers

    // Draw a line under the headers
    painter.drawLine(margin, yPosition, writer.width() - margin, yPosition);
    yPosition += 10;  // Space after the line

    // Fetch employee data from the database and write to the PDF
    QSqlQuery query;
    query.prepare("SELECT id_Employe, nom, prenom, poste, date_embauche, salaire FROM Employes");

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString nom = query.value(1).toString();
            QString prenom = query.value(2).toString();
            QString poste = query.value(3).toString();
            QString dateEmb = query.value(4).toDate().toString();
            double salaire = query.value(5).toDouble();

            // Draw each employee's data in a row
            painter.setFont(QFont("Arial", 10));  // Smaller font for table rows
            painter.drawText(margin + 10, yPosition, QString::number(id));
            painter.drawText(margin + 110, yPosition, nom + " " + prenom);
            painter.drawText(margin + 310, yPosition, poste);
            painter.drawText(margin + 410, yPosition, dateEmb);
            painter.drawText(margin + 530, yPosition, QString::number(salaire, 'f', 2));

            // Move down for the next row
            yPosition += 25; // Increase space between rows

            // Draw a line under the row (border for the table)
            painter.drawLine(margin, yPosition, writer.width() - margin, yPosition);
            yPosition += 5;  // Space between rows
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to fetch employee data for PDF.");
        painter.end();
        return;
    }

    // End the painter and finalize the PDF
    painter.end();

    // Notify the user
    QMessageBox::information(this, "Success", "PDF saved successfully.");
}
bool mainservice::validateLogin(const QString &username, const QString &password) {

    const QString correctUsername = "admin";
    const QString correctPassword = "taki";



    return (username == correctUsername && password == correctPassword);
}

void mainservice::onLoginButtonClicked() {

    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();


    if (validateLogin(username, password)) {

        ui->stackedWidget->setCurrentIndex(0);
    } else {

        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}
