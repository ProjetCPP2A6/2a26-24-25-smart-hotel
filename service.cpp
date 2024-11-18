#include <QSqlError>
#include <QVariant>
#include "service.h"

// Constructor
service::service(int id_service, QString nom_service, QString etat, QString categorie, int cout) {
    this->id_service = id_service;
    this->nom_service = nom_service;
    this->etat = etat;
    this->categorie = categorie;
    this->cout = cout;
}

// Getters
int service::getIdService() {
    return id_service;
}

QString service::getNomService() {
    return nom_service;
}

QString service::getEtat() {
    return etat;
}

QString service::getCategorie() {
    return categorie;
}

int service::getCout() {
    return cout;
}

// Setters
void service::setIdService(int id_service) {
    this->id_service = id_service;
}

void service::setNomService(QString nom_service) {
    this->nom_service = nom_service;
}

void service::setEtat(QString etat) {
    this->etat = etat;
}

void service::setCategorie(QString categorie) {
    this->categorie = categorie;
}

void service::setCout(int cout) {
    this->cout = cout;
}

// Add service to the database
bool service::addServiceToDB() {
    QSqlQuery query;

    // Convert id_service and cout to QString
    QString res_id_service = QString::number(id_service);
    QString res_cout = QString::number(cout);

    // Prepare the query with matching column names from the Services table
    query.prepare("INSERT INTO Services (id_service, nom_service, etat, categorie, cout) VALUES (:id_service, :nom_service, :etat, :categorie, :cout)");

    // Bind values to placeholders
    query.bindValue(":id_service", res_id_service);       // Using res_id_service for id_service
    query.bindValue(":nom_service", nom_service);
    query.bindValue(":etat", etat);
    query.bindValue(":categorie", categorie);
    query.bindValue(":cout", res_cout);                   // Using res_cout for cout

    // Execute the query and return success status
    if (query.exec()) {
        return true;
    } else {
        qWarning() << "Error adding service to DB:" << query.lastError().text();
        return false;
    }
}

// Fetch all services from the database
QSqlQueryModel* service::fetchAllServices() {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Ensure the query sorts the results by 'cout' in ascending order
    query.prepare("SELECT id_service, nom_service, etat, categorie, cout FROM Services ORDER BY cout ASC");

    if (query.exec()) {
        model->setQuery(query); // Set the sorted query result
    } else {
        qWarning() << "Error fetching and sorting services:" << query.lastError().text();
    }

    return model; // Return the model for the caller
}

// Delete service from the database
bool service::deleteServiceFromDB(int id_service) {
    QSqlQuery query;
    QString res_id_service = QString::number(id_service);
    query.prepare("DELETE FROM Services WHERE id_service = :id_service");
    query.bindValue(":id_service", res_id_service);

    if (query.exec()) {
        // Check how many rows were affected
        if (query.numRowsAffected() > 0) {
            return true; // Successfully deleted
        } else {
            return false; // No rows affected, meaning the ID was not found
        }
    } else {
        qWarning() << "Error deleting service from DB:" << query.lastError().text();
        return false; // Query execution failed
    }
}

// Edit service in the database
bool service::editServiceInDB(int id_service, QString newEtat, double newCout) {
    QSqlQuery query;
    query.prepare("UPDATE Services SET etat = :etat, cout = :cout WHERE id_service = :id_service");
    query.bindValue(":etat", newEtat);
    query.bindValue(":cout", QString::number(newCout)); // Convert cout to QString
    query.bindValue(":id_service", QString::number(id_service)); // Convert id_service to QString

    if (query.exec()) {
        return true; // Successfully edited
    } else {
        qWarning() << "Error editing service in DB:" << query.lastError().text();
        return false; // Not found or error
    }
}
QSqlQueryModel* service::displayAllServices() {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Prepare and execute the query to select all services
    query.prepare("SELECT * FROM Services");

    if (query.exec()) {
        model->setQuery(query); // Assign the query result to the model
    } else {
        qWarning() << "Error displaying all services:" << query.lastError().text();
    }

    return model; // Return the model for display in QTableView
}
