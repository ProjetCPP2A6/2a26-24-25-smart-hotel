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


mainservice::mainservice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainservice)
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

}

mainservice::~mainservice()
{
    delete ui;
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

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);


    int id_employe = ui->lineEdit_sr->text().toInt();
    if (id_employe <= 0) {
        QMessageBox::warning(this, "Warning", "Please enter a valid employe ID.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id_Employe, nom, prenom, poste, date_embauche, salaire FROM Employes WHERE id_Employe = :id_Employe");
    query.bindValue(":id_Employe", id_employe);


    if (query.exec()) {

        if (query.next()) {

            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);


            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(query.value(5).toString()));
        } else {

            QMessageBox::warning(this, "Error", "No employe found with the given ID.");
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
