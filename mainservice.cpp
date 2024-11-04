#include "mainservice.h"
#include "ui_mainservice.h"
#include <QMessageBox>
#include "employe.h"
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
    // Get input values from the UI
    int id = ui->lineEdit_id->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString poste = ui->lineEdit_poste->text();
    QDate date_embauche = ui->dateEdit_embauche->date();
    double salaire = ui->lineEdit_salaire->text().toDouble();


    employe newEmploye(id, nom, prenom, poste, date_embauche, salaire);

    if (newEmploye.addEmployeToDB()) {
        QMessageBox::information(this, "Success", "Employe added successfully!");


        ui->lineEdit_id->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_prenom->clear();
        ui->lineEdit_poste->clear();
        ui->dateEdit_embauche->clear();
        ui->lineEdit_salaire->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add employe.");
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

void mainservice::on_pushButton_edit_clicked()
{

    int id_employe = ui->lineEdit_id_ed->text().toInt();


    QString newPoste = ui->lineEdit_poste_ed->text();
    double newSalaire = ui->lineEdit_salaire_ed->text().toDouble();


    QString nom = "";
    QString prenom = "";
    QDate date_embauche = QDate();
    employe employeToEdit(id_employe, nom, prenom, newPoste, date_embauche, newSalaire);


    if (employeToEdit.editEmployeInDB(id_employe, nom, prenom, newPoste, date_embauche, newSalaire)) {
        QMessageBox::information(this, "Success", "Employe updated successfully.");


        ui->lineEdit_id_ed->clear();
        ui->lineEdit_poste_ed->clear();
        ui->lineEdit_salaire_ed->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update employe. Check the ID.");
    }
}

