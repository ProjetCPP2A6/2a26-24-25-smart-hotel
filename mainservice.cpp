#include "mainservice.h"
#include "ui_mainservice.h"
#include <QMessageBox>
#include "service.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "mailhandler.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <vector>
#include <QStandardItemModel>
struct Service {
    int id;
    QString name;
    QString state;
    QString category;
    double cost;
};

std::vector<Service> services;

mainservice::mainservice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainservice)
{
    ui->setupUi(this);

    // Validator for ID and cout fields (positive integers, max 8 digits)
    QRegularExpression reIdCout("^\\d{1,8}$");
    QValidator *idCoutValidator = new QRegularExpressionValidator(reIdCout, this);
    ui->lineEdit_id->setValidator(idCoutValidator);
    ui->lineEdit_cout->setValidator(idCoutValidator);
    ui->lineEdit_idSP->setValidator(idCoutValidator);
    ui->lineEdit_id_ed->setValidator(idCoutValidator);
    ui->lineEdit_cout_ed->setValidator(idCoutValidator);

    // Validator for character-only fields (nom, etat, categorie)
    QRegularExpression reCharacters("^[A-Za-z\\s]+$");
    QValidator *charValidator = new QRegularExpressionValidator(reCharacters, this);
    ui->lineEdit_nom->setValidator(charValidator);
    ui->lineEdit_etat->setValidator(charValidator);
    ui->lineEdit_categorie->setValidator(charValidator);
    ui->lineEdit__etat_ed->setValidator(charValidator);

}

mainservice::~mainservice()
{
    delete ui;
}

void mainservice::on_pushButton_ajouter_clicked() {
    int id = ui->lineEdit_id->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString etat = ui->lineEdit_etat->text();
    QString categorie = ui->lineEdit_categorie->text();
    double cout = ui->lineEdit_cout->text().toDouble();

    service newService(id, nom, etat, categorie, cout);

    if (newService.addServiceToDB()) {
        QMessageBox::information(this, "Success", "Service added successfully!");
        ui->lineEdit_id->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_etat->clear();
        ui->lineEdit_categorie->clear();
        ui->lineEdit_cout->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add service.");
    }
}

void mainservice::on_pushButton_supprimer_clicked() {
    int id_service = ui->lineEdit_idSP->text().toInt();
    service serviceToDelete(id_service, "", "", "", 0);

    if (serviceToDelete.deleteServiceFromDB(id_service)) {
        QMessageBox::information(this, "Success", "Service deleted successfully.");
        ui->lineEdit_idSP->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete service. Check the ID.");
    }
}

void mainservice::on_pushButton_afficher_clicked() {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    int id_service = ui->lineEdit_sr->text().toInt();
    if (id_service <= 0) {
        QMessageBox::warning(this, "Warning", "Please enter a valid service ID.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id_service, nom_service, etat, categorie, cout FROM Services WHERE id_service = :id_service");
    query.bindValue(":id_service", id_service);

    if (query.exec()) {
        if (query.next()) {
            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);

            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(query.value(4).toString()));
        } else {
            QMessageBox::warning(this, "Error", "No service found with the given ID.");
        }
    } else {
        qDebug() << "Query execution failed:" << query.lastError().text();
        QMessageBox::warning(this, "Error", "Failed to execute query.");
    }
}

void mainservice::on_pushButton_edit_clicked() {
    int id_service = ui->lineEdit_id_ed->text().toInt();
    QString newEtat = ui->lineEdit__etat_ed->text();
    double newCout = ui->lineEdit_cout_ed->text().toDouble();

    // Check if the service with the given ID exists in the database
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Services WHERE id_service = :id_service");
    query.bindValue(":id_service", id_service);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count == 0) {
            QMessageBox::warning(this, "Error", "No service found with the given ID. Update failed.");
            return;
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to check service existence.");
        return;
    }

    // If the ID exists, proceed with the update
    service serviceToEdit(id_service, "", "", "", newCout);
    if (serviceToEdit.editServiceInDB(id_service, newEtat, newCout)) {
        QMessageBox::information(this, "Success", "Service updated successfully.");
        ui->lineEdit_id_ed->clear();
        ui->lineEdit__etat_ed->clear();
        ui->lineEdit_cout_ed->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update service. Check the ID.");
    }
}

void mainservice::on_pushButton_display_clicked() {
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);

    service svc(0, "", "", "", 0);
    QSqlQueryModel* model = svc.fetchAllServices();

    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableWidget_2->insertRow(i);
        ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
        ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
        ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 3)).toString()));
        ui->tableWidget_2->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 4)).toString()));
    }

    delete model;
}



void mainservice::on_pushButton_sendEmail_clicked()
{

    QString status;
    Smtp* smtp = new Smtp("smart.hotel.2a26@gmail.com","apmicbjhbqqguvlw", "smtp.gmail.com", 465); //smtp.gmail.com //iltm krbu hrvr bgye
    smtp->sendMail("smart.hotel.2a26@gmail.com", ui->lineEdit_recipient->text() , ui->lineEdit_subject->text() ,ui->textEdit->toPlainText());
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );

    }




    void mainservice::on_btnRoomCleaned_clicked()
    {
        ui->lineEdit_subject->setText("Room Preparation Complete");
        ui->textEdit->setText("Dear [Manager Name],\n\nThe room [Room Number] is now cleaned and ready for the next guest. "
                                   "Please confirm if any additional setup is required.\n\nBest regards,\nSerenity Haven Team");
    }


    void mainservice::on_DealsPromotions_clicked()
    {
        ui->lineEdit_subject->setText("Exclusive Deals for Our Valued Guests!");
        ui->textEdit->setText("Dear [Client Name],\n\nWe’re thrilled to offer you an exclusive promotion:\n\n"
                                   "Stay 3 nights and get the 4th night free!\n20% off all spa treatments.\n\n"
                                   "Don’t miss out—this offer is valid until [date]. Book now to enjoy the luxury you deserve.\n"
                                   "[Book Now Button]\n\nWarm regards,\nSerenity Haven");
    }



    void mainservice::on_ShiftNotifications_clicked()
    {
        ui->lineEdit_subject->setText("Your Upcoming Shift Schedule");
        ui->textEdit->setText("Dear [Employee Name],\n\nYour updated shift schedule for the upcoming week is as follows:\n\n"
                                   "[Date]: [Shift Time]\n[Date]: [Shift Time]\n\n"
                                   "Please contact your supervisor if there are any issues.\n\nThank you,\nSerenity Haven HR Team");

    }


    void mainservice::on_DealsPromotions_2_clicked()
    {
        ui->lineEdit_subject->setText("Special Room Setup Request Confirmation");
        ui->textEdit->setText("Dear [Client Name],\n\nWe are pleased to inform you that your special request for [flowers, chocolates, etc.] "
                                   "in room [Room Number] has been arranged as per your instructions.\n\nIf you have additional preferences, please contact us directly.\n\n"
                                   "Best regards,\nSerenity Haven");
    }


    void mainservice::on_InventoryAlert_clicked()
    {
        ui->lineEdit_subject->setText("Low Inventory Alert");
        ui->textEdit->setText("Dear [Logistics Manager],\n\nThe inventory for [Item Name] has reached a critical level. Current stock: [Quantity].\n\n"
                                   "Please restock promptly to avoid disruption.\n\nThank you,\nSerenity Haven Inventory System");
    }




    void mainservice::on_DeliveryConfirmation_clicked()
    {
        ui->lineEdit_subject->setText("Delivery Received");
        ui->textEdit->setText("Dear [Supplier Name],\n\nWe confirm the receipt of your delivery for [Item Description]. The details are as follows:\n\n"
                                   "Quantity: [Quantity]\nDelivery Date: [Date]\n\nThank you for your prompt service.\n\n"
                                   "Best regards,\nSerenity Haven Logistics Team");
    }


    void mainservice::on_searchevent_clicked()
    {
        QString searchQuery = ui->lineEdit_search->text(); // Get the search query from the line edit
        bool found = false; // Flag to indicate if an event was found

        // Iterate through all events stored in the 'events' map
        for (auto it = events.begin(); it != events.end(); ++it)
        {
            // Check if the event name matches the search query
            if (it.value().first.contains(searchQuery, Qt::CaseInsensitive))
            {
                // If a match is found, display the event details in the event details text box
                QString eventDetails = "Date: " + it.key().toString("yyyy-MM-dd") + "\nEvent Name: " + it.value().first +
                                       "\nDescription: " + it.value().second;
                ui->textEdit_eventDetails->setText(eventDetails); // Set the event details to the text edit
                found = true;
                break; // Exit the loop once the first match is found
            }
        }

        // If no event is found, display a message
        if (!found)
        {
            ui->textEdit_eventDetails->setText("No events found matching the search query.");
        }
    }

    void mainservice::on_AddEvent_clicked()
    {
        QDate selectedDate = ui->calendarWidget->selectedDate(); // Get the selected date from the calendar
        QString eventName = ui->lineEdit_eventName->text(); // Get the event name from the line edit
        QString eventDescription = ui->textEdit_description->toPlainText(); // Get the event description from the text edit

        if (!eventName.isEmpty() && !eventDescription.isEmpty()) // Ensure both fields are filled
        {
            // Store the event in the events map (using the date as the key)
            events[selectedDate] = qMakePair(eventName, eventDescription);

            // Clear the input fields after adding the event
            ui->lineEdit_eventName->clear();
            ui->textEdit_description->clear();

            // Show success message
            QMessageBox::information(this, "Event Added", "The event has been successfully added!");
        }
        else
        {
            // If either the name or description is empty, show an error message
            QMessageBox::warning(this, "Error", "Please fill in both the Event Name and Description.");
        }
    }

    void mainservice::on_calendarWidget_activated(const QDate &date)
    {
        // Check if there's an event for the selected date
        if (events.contains(date))
        {
            auto event = events.value(date);
            QString eventDetails = "Event Name: " + event.first + "\nDescription: " + event.second;
            ui->textEdit_eventDetails->setText(eventDetails);
        }
        else
        {
            ui->textEdit_eventDetails->setText("No events for the selected date.");
        }
    }






    void mainservice::on_pushButton_exportpdf_clicked()
    {
        // Prompt user to choose file location
        QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
        if (fileName.isEmpty()) {
            return;
        }

        // Create PDF writer
        QPdfWriter pdfWriter(fileName);
        pdfWriter.setPageSize(QPageSize::A4);
        pdfWriter.setResolution(300);

        QPainter painter(&pdfWriter);

        // Margins and table setup
        int margin = 100;
        int tableStartX = margin;
        int tableStartY = 400;
        int rowHeight = 50;
        int colWidths[] = {100, 200, 200, 200, 100}; // Adjust for ID, Name, State, Category, Cost

        // Title
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(margin, 200, "Services Data");

        // Draw table headers
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        int currentX = tableStartX;
        int currentY = tableStartY;

        QStringList headers = {"ID", "Name", "State", "Category", "Cost"};
        for (int i = 0; i < headers.size(); i++) {
            painter.drawRect(currentX, currentY, colWidths[i], rowHeight);
            painter.drawText(currentX + 10, currentY + rowHeight / 2, headers[i]);
            currentX += colWidths[i];
        }

        // Draw table data
        painter.setFont(QFont("Arial", 10));
        currentY += rowHeight;

        for (const Service& service : services) {
            currentX = tableStartX;

            QStringList rowData = {
                QString::number(service.id),
                service.name,
                service.state,
                service.category,
                QString::number(service.cost, 'f', 2)
            };

            for (int i = 0; i < rowData.size(); i++) {
                painter.drawRect(currentX, currentY, colWidths[i], rowHeight);
                painter.drawText(currentX + 10, currentY + rowHeight / 2, rowData[i]);
                currentX += colWidths[i];
            }

            currentY += rowHeight;

            // Check for page overflow
            if (currentY > pdfWriter.height() - margin) {
                pdfWriter.newPage();
                currentY = tableStartY;

                // Redraw headers on the new page
                currentX = tableStartX;
                for (int i = 0; i < headers.size(); i++) {
                    painter.drawRect(currentX, currentY, colWidths[i], rowHeight);
                    painter.drawText(currentX + 10, currentY + rowHeight / 2, headers[i]);
                    currentX += colWidths[i];
                }

                currentY += rowHeight;
            }
        }

        painter.end();

        // Notify success
        QMessageBox::information(this, "Export Successful", "The data has been exported to " + fileName);
    }

    void mainservice::on_pushButton_Stat_clicked() {
        QSqlQuery query;
        int activeCount = 0, inactiveCount = 0;

        // Query to count active and inactive services
        query.prepare("SELECT etat, COUNT(*) FROM Services GROUP BY etat");

        if (query.exec()) {
            while (query.next()) {
                QString etat = query.value(0).toString();
                int count = query.value(1).toInt();

                if (etat.toLower() == "active") {
                    activeCount += count;
                } else {
                    inactiveCount += count;
                }
            }
        } else {
            qWarning() << "Error fetching state statistics:" << query.lastError().text();
            return;
        }

        // Populate the table view
        QStandardItemModel* model = new QStandardItemModel(2, 2, this);
        model->setHorizontalHeaderLabels(QStringList() << "State" << "Count");

        model->setItem(0, 0, new QStandardItem("Active"));
        model->setItem(0, 1, new QStandardItem(QString::number(activeCount)));

        model->setItem(1, 0, new QStandardItem("Not Active"));
        model->setItem(1, 1, new QStandardItem(QString::number(inactiveCount)));

        ui->tableView_stat->setModel(model);
        ui->tableView_stat->resizeColumnsToContents();
    }
