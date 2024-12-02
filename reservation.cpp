#include "reservation.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QSqlRecord>
#include <QDebug>
#include <QFileDialog>
#include <QTextDocument>

// Constructeur
reservation::reservation(int id_reservation, int id_client, QString type_reservation, QDate date_debut, QDate date_fin,
                         int nb_personnes, QString statut, double montant, QString mode_paiement)
    : id_reservation(id_reservation), id_client(id_client), type_reservation(type_reservation), date_debut(date_debut),
    date_fin(date_fin), nb_personnes(nb_personnes), statut(statut), montant(montant), mode_paiement(mode_paiement)
{
}

// Ajouter une réservation
bool reservation::ajouter()
{
    if (id_reservation <= 0 || id_client <= 0 || nb_personnes <= 0 || montant < 0) {
        QMessageBox::warning(nullptr, "Erreur", "Les valeurs numériques doivent être positives et valides.");
        return false;
    }

    if (type_reservation.isEmpty() || statut.isEmpty() || mode_paiement.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez remplir tous les champs de texte.");
        return false;
    }

    if (date_debut >= date_fin) {
        QMessageBox::warning(nullptr, "Erreur", "La date de début doit être antérieure à la date de fin.");
        return false;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO reservation (id_reservation, id_client, type_reservation, date_debut, date_fin, nb_personnes, statut,  mode_paiement, montant)"
                  "VALUES (:id_reservation, :id_client, :type_reservation, :date_debut, :date_fin, :nb_personnes, :statut,:mode_paiement,:montant)");

    query.bindValue(":id_reservation", id_reservation);
    query.bindValue(":id_client", id_client);
    query.bindValue(":type_reservation", type_reservation);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);
    query.bindValue(":nb_personnes", nb_personnes);
    query.bindValue(":statut", statut);
    query.bindValue(":mode_paiement", mode_paiement);
    query.bindValue(":montant", montant);


    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de l'ajout de la réservation : " + query.lastError().text());
        return false;
    }
    return true;
}

// Supprimer une réservation
bool reservation::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM reservation WHERE id_reservation = :id_reservation");
    query.bindValue(":id_reservation", id);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la suppression de la réservation : " + query.lastError().text());
        return false;
    }
    return true;
}

// Modifier une réservation
bool reservation::modifier(int id_reservation)
{QSqlQuery query;
    query.prepare("UPDATE reservation SET id_client = :id_client, type_reservation = :type_reservation, "
                  "date_debut = :date_debut, date_fin = :date_fin, nb_personnes = :nb_personnes, "
                  "statut = :statut, montant = :montant, mode_paiement = :mode_paiement "
                  "WHERE id_reservation = :id_reservation");

    query.bindValue(":id_reservation", id_reservation);
    query.bindValue(":id_client", id_client);
    query.bindValue(":type_reservation", type_reservation);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);
    query.bindValue(":nb_personnes", nb_personnes);
    query.bindValue(":statut", statut);
    query.bindValue(":montant", montant);
    query.bindValue(":mode_paiement", mode_paiement);

    return query.exec();
}

#include "reservation.h"

QSqlQueryModel* reservation::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Exécution de la requête pour récupérer les réservations
    QSqlQuery query;
    query.prepare("SELECT * FROM reservation");  // Utilisez la table correspondante dans votre base de données
    query.exec();
model->setQuery(std::move(query));  // Charger les résultats dans le modèle

    // Définir les en-têtes des colonnes selon les noms des attributs
    model->setHeaderData(0, Qt::Horizontal, "id_reservation");
    model->setHeaderData(1, Qt::Horizontal, "id_client");
    model->setHeaderData(2, Qt::Horizontal, "type_reservation");
    model->setHeaderData(3, Qt::Horizontal, "date_debut");
    model->setHeaderData(4, Qt::Horizontal, "date_fin");
    model->setHeaderData(5, Qt::Horizontal, "nb_personnes");
    model->setHeaderData(6, Qt::Horizontal, "statut");
    model->setHeaderData(7, Qt::Horizontal, "montant");
    model->setHeaderData(8, Qt::Horizontal, "mode_paiement");

    return model;
}
// Trier les réservations par critère et ordre spécifiés
QSqlQuery reservation::trier(QString critere)
{
    QSqlQuery query;

    // Vérification que le critère de tri est valide
    QStringList valid_criteria = {"date_debut", "montant", "statut"};
    if (!valid_criteria.contains(critere)) {
        qDebug() << "Critère de tri invalide.";
        return query;
    }

    // Tri décroissant, l'ordre est fixe à "DESC"
    query.prepare("SELECT * FROM reservation ORDER BY " + critere + " DESC");

    // Exécution de la requête SQL
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de tri : " << query.lastError().text();
    }

    return query;
}
/*bool reservation::rechercher(int id_reservation) {
    QSqlQuery query;
    query.prepare("SELECT * FROM reservation WHERE id_reservation = :id_reservation");
    query.bindValue(":id_reservation", id_reservation);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de recherche : " << query.lastError().text();
        return false;
    }

    if (query.next()) {
        // Si une ligne est trouvée, la réservation existe
        return true;
    } else {
        // Aucune ligne trouvée, la réservation n'existe pas
        return false;
    }
}*/
QSqlQueryModel* reservation::rechercher(const QString& critere, const QString& value) {
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();

    // Préparer la requête en fonction du critère
    if (critere == "id_reservation") {
        query.prepare("SELECT * FROM reservation WHERE ID_RESERVATION = :value");
        query.bindValue(":value", value.toInt());  // Convertir la valeur en entier
    } else if (critere == "id_client") {
        query.prepare("SELECT * FROM reservation WHERE ID_CLIENT = :value");
        query.bindValue(":value", value.toInt());  // Convertir la valeur en entier
    } else if (critere == "montant") {
        query.prepare("SELECT * FROM reservation WHERE MONTANT = :value");
        query.bindValue(":value", value.toDouble());  // Convertir la valeur en double
    }

    // Exécuter la requête
    if (query.exec()) {
        model->setQuery(query);  // Charger les résultats dans le modèle
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError().text();
    }

    return model;  // Retourner le modèle avec les résultats
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
