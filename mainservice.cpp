#include "mainservice.h"
#include "ui_mainservice.h"
#include <QMessageBox>
#include "service.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

mainservice::mainservice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainservice)
{
    ui->setupUi(this);
}

mainservice::~mainservice()
{
    delete ui;
}




void mainservice::on_pushButton_ajouter_clicked() {
    // Get input values from the UI (assuming you have QLineEdit for each field)
    int id = ui->lineEdit_id->text().toInt(); // Assuming you have a lineEdit for ID
    QString nom = ui->lineEdit_nom->text(); // Assuming you have a lineEdit for Nom
    QString etat = ui->lineEdit_etat->text(); // Assuming you have a lineEdit for Etat
    QString categorie = ui->lineEdit_categorie->text(); // Assuming you have a lineEdit for Categorie
    double cout = ui->lineEdit_cout->text().toDouble(); // Assuming you have a lineEdit for Cout

    // Create a new service instance
    service newService(id, nom, etat, categorie, cout);

    // Attempt to add the service to the database
    if (newService.addServiceToDB()) {

        QMessageBox::information(this, "Success", "Service added successfully!");

        // Optionally clear input fields after successful addition
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
    // Get the ID of the service to delete from the input field
    int id_service = ui->lineEdit_idSP->text().toInt(); // Assuming you reuse lineEdit for ID input

    // Create an instance of the service class to use for deletion
    service serviceToDelete(id_service, "", "", "", 0); // Use default values for other fields

    // Attempt to delete the service from the database
    if (serviceToDelete.deleteServiceFromDB(id_service)) {
        QMessageBox::information(this, "Success", "Service deleted successfully.");

        // Optionally clear the input field after deletion
        ui->lineEdit_id->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete service. Check the ID.");
    }
}



void mainservice::on_pushButton_afficher_clicked() {
    // Clear previous contents and reset the row count
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Get the ID of the service from the input field
    int id_service = ui->lineEdit_sr->text().toInt();
    if (id_service <= 0) {
        QMessageBox::warning(this, "Warning", "Please enter a valid service ID.");
        return; // Exit if the ID is not valid
    }

    QSqlQuery query;
    query.prepare("SELECT id_service, nom_service, etat, categorie, cout FROM Services WHERE id_service = :id_service");
    query.bindValue(":id_service", id_service);

    // Execute the query and check if it succeeded
    if (query.exec()) {
        // Check if a record was found
        if (query.next()) {
            // Insert a new row for the fetched service
            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);

            // Set the items in the QTableWidget
            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(query.value(1).toString())); // Nom
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(query.value(2).toString())); // Etat
            ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(query.value(3).toString())); // Categorie
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(query.value(4).toString())); // Cout
        } else {
            // No record found for the given ID
            QMessageBox::warning(this, "Error", "No service found with the given ID.");
        }
    } else {
        // Query execution failed
        qDebug() << "Query execution failed:" << query.lastError().text();
        QMessageBox::warning(this, "Error", "Failed to execute query.");
    }
}









void mainservice::on_pushButton_edit_clicked()
{
    // Get the ID of the service to edit from the input field
    int id_service = ui->lineEdit_id_ed->text().toInt(); // Assuming you reuse lineEdit for ID input

    // Get the new values for etat and cout from the UI
    QString newEtat = ui->lineEdit__etat_ed->text(); // Assuming you have a lineEdit for the new Etat
    double newCout = ui->lineEdit_cout_ed->text().toDouble(); // Assuming you have a lineEdit for the new Cout

    // Attempt to edit the service in the database
    service serviceToEdit(id_service, "", "", "", newCout); // Use the existing ID and new values
    if (serviceToEdit.editServiceInDB(id_service, newEtat, newCout)) {
        QMessageBox::information(this, "Success", "Service updated successfully.");

        // Optionally clear input fields after successful update
        ui->lineEdit_id_ed->clear();
        ui->lineEdit__etat_ed->clear();
        ui->lineEdit_cout_ed->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update service. Check the ID.");
    }
}

