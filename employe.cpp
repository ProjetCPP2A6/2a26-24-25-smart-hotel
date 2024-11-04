#include <QSqlError>
#include <QVariant>
#include "employe.h"


employe::employe(int id_Employe, QString nom, QString prenom, QString poste, QDate date_embauche, double salaire) {
    this->id_Employe = id_Employe;
    this->nom = nom;
    this->prenom = prenom;
    this->poste = poste;
    this->date_embauche = date_embauche;
    this->salaire = salaire;
}


int employe::getIdEmploye() {
    return id_Employe;
}

QString employe::getNom() {
    return nom;
}

QString employe::getPrenom() {
    return prenom;
}

QString employe::getPoste() {
    return poste;
}

QDate employe::getDateEmbauche() {
    return date_embauche;
}

double employe::getSalaire() {
    return salaire;
}

// Setters
void employe::setIdEmploye(int id_Employe) {
    this->id_Employe = id_Employe;
}

void employe::setNom(QString nom) {
    this->nom = nom;
}

void employe::setPrenom(QString prenom) {
    this->prenom = prenom;
}

void employe::setPoste(QString poste) {
    this->poste = poste;
}

void employe::setDateEmbauche(QDate date_embauche) {
    this->date_embauche = date_embauche;
}

void employe::setSalaire(double salaire) {
    this->salaire = salaire;
}


bool employe::addEmployeToDB() {
    QSqlQuery query;


    query.prepare("INSERT INTO Employes (id_Employe, nom, prenom, poste, date_embauche, salaire) "
                  "VALUES (:id_Employe, :nom, :prenom, :poste, :date_embauche, :salaire)");


    query.bindValue(":id_Employe", id_Employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":date_embauche", date_embauche);
    query.bindValue(":salaire", salaire);


    if (query.exec()) {
        return true;
    } else {
        qWarning() << "Error adding employe to DB:" << query.lastError().text();
        return false;
    }
}


QSqlQueryModel* employe::fetchAllEmployes() {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;


    query.prepare("SELECT * FROM Employes");


    if (query.exec()) {

        model->setQuery(std::move(query));
    } else {
        qWarning() << "Error fetching employes from DB:" << query.lastError().text();
        delete model;
        model = nullptr;
    }

    return model;
}



bool employe::deleteEmployeFromDB(int id_Employe) {
    QSqlQuery query;
    query.prepare("DELETE FROM Employes WHERE id_Employe = :id_Employe");
    query.bindValue(":id_Employe", id_Employe);

    if (query.exec()) {

        if (query.numRowsAffected() > 0) {
            return true;
        } else {
            return false;
        }
    } else {
        qWarning() << "Error deleting employe from DB:" << query.lastError().text();
        return false;
    }
}


bool employe::editEmployeInDB(int id_Employe, QString newNom, QString newPrenom, QString newPoste, QDate newDateEmbauche, double newSalaire) {
    QSqlQuery query;
    query.prepare("UPDATE Employes SET nom = :nom, prenom = :prenom, poste = :poste, date_embauche = :date_embauche, salaire = :salaire WHERE id_Employe = :id_Employe");
    query.bindValue(":nom", newNom);
    query.bindValue(":prenom", newPrenom);
    query.bindValue(":poste", newPoste);
    query.bindValue(":date_embauche", newDateEmbauche);
    query.bindValue(":salaire", newSalaire);
    query.bindValue(":id_Employe", id_Employe);

    if (query.exec()) {
        return true;
    } else {
        qWarning() << "Error editing employe in DB:" << query.lastError().text();
        return false;
    }
}
