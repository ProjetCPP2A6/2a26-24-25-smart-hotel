#include "reservation.h"
#include <QSqlQuery>
#include <QMessageBox>
#include<QObject>
#include<QSqlQueryModel>


#include <QSqlError>
#include <QPrinter>
#include <QPainter>
#include <QSqlRecord>
#include <QDebug>
#include <QFileDialog>
#include <QTextDocument>
reservation::reservation()
{
    id_reservation = 0;
    id_client = 0;
    type_reservation = "";
    date_debut = QDate();
    date_fin = QDate();
    nb_personnes = 0;
    statut = "";
    mode_paiement = "";
    montant = 0.0;
    numt = 0;


}

reservation::reservation(int id_reservation, int id_client, QString type_reservation,
                         QDate date_debut, QDate date_fin, int nb_personnes, QString statut,
                         QString mode_paiement ,double montant , int numt)
{
    this->id_reservation = id_reservation;
    this->id_client = id_client;
    this->type_reservation = type_reservation;
    this->date_debut = date_debut;
    this->date_fin = date_fin;
    this->nb_personnes = nb_personnes;
    this->statut = statut;
    this->mode_paiement = mode_paiement;
    this->montant = montant;
    this->numt = numt;

}

// Ajouter une réservation
bool reservation::ajouter1()
{
    QSqlQuery query;

    query.prepare("INSERT INTO gs_reservation (id_reservation, id_client, type_reservation, "
                  "date_debut, date_fin, nb_personnes, statut,mode_paiement, montant,numt ) "
                  "VALUES (:id_reservation, :id_client, :type_reservation, :date_debut, :date_fin, "
                  ":nb_personnes, :statut,:mode_paiement, :montant, :numt)");

    query.bindValue(":id_reservation", id_reservation);
    query.bindValue(":id_client", id_client);
    query.bindValue(":type_reservation", type_reservation);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);
    query.bindValue(":nb_personnes", nb_personnes);
    query.bindValue(":statut", statut);
    query.bindValue(":mode_paiement", mode_paiement);
    query.bindValue(":montant", montant);
    query.bindValue(":numt", numt);


    return query.exec();
}

// Supprimer une réservation
bool reservation::supprimer1(int id_reservation)
{
    QSqlQuery query;
    query.prepare("DELETE FROM gs_reservation WHERE id_reservation = :id_reservation");
    query.bindValue(":id_reservation", id_reservation);
    return query.exec();
}

// Modifier une réservation
bool reservation::modifier1(int id_reservation, int id_client, QString type_reservation,QDate date_debut, QDate date_fin, int nb_personnes, QString statut,QString mode_paiement ,double montant , int numt)
{
    QSqlQuery query;
    query.prepare("UPDATE gs_reservation SET id_client = :id_client, type_reservation = :type_reservation, "
                  " date_debut = :date_debut,date_fin = :date_fin, "
                  "nb_personnes = :nb_personnes, statut = :statut, "
                  "mode_paiement = :mode_paiement, montant = :montant , numt = :numt"
                  "WHERE id_reservation = :id_reservation");

    query.bindValue(":id_client", id_client);
    query.bindValue(":type_reservation", type_reservation);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);
    query.bindValue(":nb_personnes", nb_personnes);
    query.bindValue(":statut", statut);
    query.bindValue(":mode_paiement", mode_paiement);
    query.bindValue(":montant", montant);
    query.bindValue(":numt", numt);
     query.bindValue(":id_reservation", id_reservation);



    return query.exec();
}

// Afficher toutes les réservations
QSqlQueryModel* reservation::afficher1()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM gs_reservation");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Reservation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type_reservation"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Debut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date_Fin"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nb Personnes"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Mode_Paiement"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Num Telephone"));


    return model;
}


bool reservation::exporterPDF(const QString &filePath) {
    QString content;
    content.append("<h1>Détails de la réservation</h1>");
    content.append("<p>ID Réservation: " + QString::number(id_reservation) + "</p>");
    content.append("<p>ID Client: " + QString::number(id_client) + "</p>");
    content.append("<p>Type de Réservation: " + type_reservation + "</p>");
    content.append("<p>Date de Début: " + date_debut.toString() + "</p>");
    content.append("<p>Date de Fin: " + date_fin.toString() + "</p>");
    content.append("<p>Nombre de Personnes: " + QString::number(nb_personnes) + "</p>");
    content.append("<p>Statut: " + statut + "</p>");
    content.append("<p>Montant: " + QString::number(montant) + "</p>");
    content.append("<p>Mode de Paiement: " + mode_paiement + "</p>");

    // Création d'un document texte pour contenir le contenu formaté
    QTextDocument document;
    document.setHtml(content);

    // Configuration de l'imprimante pour générer un fichier PDF
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Impression du document dans le fichier PDF
    document.print(&printer);

    return true;
}


