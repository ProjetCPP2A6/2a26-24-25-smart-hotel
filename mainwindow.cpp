#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Chambre.h"
#include<QString>
#include <QMessageBox>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>
#include<QSqlError>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_ID->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_supp->setValidator(new QIntValidator(0,9999,this));
    ui->tableView->setModel(CHtmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    int idchambre=ui->lineEdit_ID->text().toInt();
    QString etat =ui->comboBox_etat->currentText();
    QString type =ui->comboBox_type->currentText();
    int tarif=ui->lineEdit_T->text().toInt();

    Chambre CH (idchambre,etat,type,tarif);
    bool test= CH.ajouter();
    if(test)
    {
        ui->tableView->setModel(CHtmp.afficher());
        QMessageBox :: information(nullptr,QObject::tr("ok"),
                                  QObject::tr("Ajout effectue/n"
                                              "click cancel to exit."),
                                  QMessageBox :: Cancel);

    }
    else
    {
        QMessageBox :: critical(nullptr,QObject::tr("Not ok"),
                               QObject::tr("Ajout non effectue/n" "click cancel to exit."),
                               QMessageBox :: Cancel);
    }
}

void MainWindow::on_comboBox_etat_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->comboBox_etat->setCurrentText("Occupée");
        break;
    case 1:
        ui->comboBox_etat->setCurrentText("Disponible");
        break;
    default :
        break;
    }
}


void MainWindow::on_comboBox_type_activated (int index)
{
    switch (index)
    {
    case 0:
        ui->comboBox_type->setCurrentText("simple");
        break;
    case 1:
        ui->comboBox_type->setCurrentText("double");
        break;
    case 2:
        ui->comboBox_type->setCurrentText("suite");
        break;
    case 3:
        ui->comboBox_type->setCurrentText("famile");
        break;
    default :
        break;
    }
}


void MainWindow::on_pushButton_Supprimer_clicked()
{


    int idchambre = ui->lineEdit_supp->text().toInt();

    // Vérifiez si l'ID de la chambre existe avant de supprimer
    QSqlQuery query;  //crée un objet de requête SQL
    query.prepare("SELECT COUNT(*) FROM gs_chambre WHERE idchambre = :idchambre"); //renvoie le nombre de lignes dans la tabl
    query.bindValue(":idchambre", idchambre);
    query.exec();

    if (query.next() && query.value(0).toInt() > 0) {
        // L'ID existe, on peut procéder à la suppression
        bool test = CHtmp.supprimer(idchambre);
        if (test) {
            ui->tableView->setModel(CHtmp.afficher());
            QMessageBox::information(this, QObject::tr("ok"),
                                     QObject::tr("Suppression effectuée.\n"
                                                 "Cliquez sur Annuler pour quitter."),
                                     QMessageBox::Cancel);
            // Effacer le champ après suppression
            ui->lineEdit_supp->clear();
        } else {
            QMessageBox::critical(this, QObject::tr("Not ok"),
                                  QObject::tr("Suppression non effectuée.\n"
                                              "Cliquez sur Annuler pour quitter."),
                                  QMessageBox::Cancel);
        }
    } else {
        // L'ID n'existe pas
        QMessageBox::warning(this, QObject::tr("Erreur"),
                             QObject::tr("L'ID spécifié n'existe pas.\n"
                                         "Veuillez vérifier l'ID et réessayer."),
                             QMessageBox::Cancel);
    }

}


void MainWindow::on_pushButton_Modifier_clicked()
{
    int idchambre = ui->lineEdit_Modifier->text().toInt();
    QString etat, type;
    int tarif;

    // Récupérer les données de la chambre
    if (getChambredata(idchambre, etat, type, tarif)) {
        // Remplir les champs avec les données récupérées
        ui->comboBox_etat_2->setCurrentText(etat);
        ui->comboBox_type_2->setCurrentText(type);
        ui->lineEdit_T_2->setText(QString::number(tarif));

        // Activer les champs pour modification
        ui->comboBox_etat_2->setEnabled(true);
        ui->comboBox_type_2->setEnabled(true);
        ui->lineEdit_T_2->setEnabled(true);

        QMessageBox::information(this, QObject::tr("Modification"), QObject::tr("Modifiez les valeurs, puis cliquez sur 'SaveModifier' pour enregistrer."));
    }
}


void MainWindow::on_comboBox_etat_2_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->comboBox_etat->setCurrentText("Occupée");
        break;
    case 1:
        ui->comboBox_etat->setCurrentText("Disponible");
        break;
    default :
        break;
    }
}




void MainWindow::on_comboBox_type_2_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->comboBox_type->setCurrentText("simple");
        break;
    case 1:
        ui->comboBox_type->setCurrentText("double");
        break;
    case 2:
        ui->comboBox_type->setCurrentText("suite");
        break;
    case 3:
        ui->comboBox_type->setCurrentText("famile");
        break;
    default :
        break;
    }
}


void MainWindow::on_pushButton_SaveModifier_clicked()
{
    int idchambre = ui->lineEdit_Modifier->text().toInt();
    QString etat = ui->comboBox_etat_2->currentText();
    QString type = ui->comboBox_type_2->currentText();
    int tarif = ui->lineEdit_T_2->text().toInt();

    if (idchambre > 0 && !etat.isEmpty() && !type.isEmpty() && tarif > 0) {
        // Appeler la méthode de modification
        bool test = CHtmp.modifier(idchambre, etat, type, tarif);
        if (test) {
            QMessageBox::information(this, QObject::tr("ok"), QObject::tr("Modification effectuée.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            ui->tableView->setModel(CHtmp.afficher()); // Actualiser la tableView

            // Désactiver les champs après la sauvegarde
            ui->comboBox_etat_2->setEnabled(false);
            ui->comboBox_type_2->setEnabled(false);
            ui->lineEdit_T_2->setEnabled(false);
        } else {
            QMessageBox::critical(this, QObject::tr("Not ok"), QObject::tr("Modification non effectuée.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::warning(this, QObject::tr("Erreur"), QObject::tr("Veuillez entrer des informations valides."));
    }


}


bool MainWindow::getChambredata(const int &idchambre,QString &etat,QString &type,int &tarif) {
    QSqlQuery query;
    query.prepare("SELECT etat,type,tarif FROM gs_chambre WHERE idchambre = :idchambre");
    query.bindValue(":idchambre", idchambre);


    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Échec de la récupération des données: " + query.lastError().text());
        return false;
    }


    if (query.next()) {
        etat = query.value("etat").toString();
        type = query.value("type").toString();
        tarif = query.value("tarif").toInt();
        return true;
    } else {
        QMessageBox::warning(this, "Erreur", "Aucune chambre trouvée avec cet ID.");
        return false;
    }
}


void MainWindow::on_pushButton_Annuler_clicked()
{
    // Efface le contenu des champs de texte
    ui->lineEdit_ID->clear();
    ui->lineEdit_T->clear();

    // Réinitialise les ComboBox à leur état par défaut (index 0)
    ui->comboBox_etat->setCurrentIndex(0);
    ui->comboBox_type->setCurrentIndex(0);
}


void MainWindow::on_pushButton_Annuler2_clicked()
{
    // Efface le contenu des champs de texte
    ui->lineEdit_supp->clear();
    ui->lineEdit_T_2->clear();

    // Réinitialise les ComboBox à leur état par défaut (index 0)
    ui->comboBox_etat_2->setCurrentIndex(0);
    ui->comboBox_type_2->setCurrentIndex(0);
}


void MainWindow::on_lineEdit_Modifier_editingFinished()
{
    int idchambre = ui->lineEdit_Modifier->text().toInt();
    QString etat, type;
    int tarif;

    // Récupérer les données de la chambre si l'ID est valide
    if (idchambre > 0) {
        getChambredata(idchambre, etat, type, tarif);
        ui->comboBox_etat_2->setCurrentText(etat);
        ui->comboBox_type_2->setCurrentText(type);
        ui->lineEdit_T_2->setText(QString::number(tarif));
    }
}


void MainWindow::on_pushButton_Annuler_3_clicked()
{
    // Efface le contenu des champs de texte
    ui->lineEdit_Modifier->clear();
    ui->lineEdit_T_2->clear();

    // Réinitialise les ComboBox à leur état par défaut (index 0)
    ui->comboBox_etat_2->setCurrentIndex(0);
    ui->comboBox_type_2->setCurrentIndex(0);
}

