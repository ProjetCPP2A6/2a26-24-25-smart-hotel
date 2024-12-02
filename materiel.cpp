#include "materiel.h"
#include <iostream>
#include <QSqlQuery>
#include <qDebug>
Materiel::Materiel() : id_materiel(0), quantite(0), id_employe(0) {}

Materiel::Materiel(int id_materiel, QString nom, QString type, int quantite,
                   QString etat, QDate date_acquisition)
    : id_materiel(id_materiel), nom(nom), type(type), quantite(quantite),
      etat(etat), date_acquisition(date_acquisition) {}
Materiel::Materiel(int id_materiel, QString nom, QString type)
    : id_materiel(id_materiel), nom(nom), type(type) {}

/*int Materiel::getIdMateriel() const { return id_materiel; }
void Materiel::setIdMateriel(int id_materiel) { this->id_materiel = id_materiel; }

std::string Materiel::getNom() const { return nom; }
void Materiel::setNom(const std::string& nom) { this->nom = nom; }

std::string Materiel::getType() const { return type; }
void Materiel::setType(const std::string& type) { this->type = type; }

int Materiel::getQuantite() const { return quantite; }
void Materiel::setQuantite(int quantite) { this->quantite = quantite; }

std::string Materiel::getEtat() const { return etat; }
void Materiel::setEtat(const std::string& etat) { this->etat = etat; }

std::string Materiel::getDateAcquisition() const { return date_acquisition; }
void Materiel::setDateAcquisition(const std::string& date_acquisition) { this->date_acquisition = date_acquisition; }

int Materiel::getIdEmploye() const { return id_employe; }
void Materiel::setIdEmploye(int id_employe) { this->id_employe = id_employe; }*/


void createTable() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS materiels ("
                "id_materiel INTEGER PRIMARY KEY AUTOINCREMENT, "
                "nom TEXT, "
                "type TEXT, "
                "quantite INTEGER, "
                "etat TEXT, "
                "date_acquisition TEXT, "
                "id_employe INTEGER)");
}


void Materiel::ajouterMateriel() {
    QSqlQuery query;
    query.prepare("INSERT INTO materiels (ID_MATERIEL,NOM, TYPE,QUANTITE, ETAT, DATE_ACQUISITION) VALUES (:ID_MATERIEL,:nom, :type, :quantite, :etat, :date_acquisition)");
    query.bindValue(":ID_MATERIEL",id_materiel);
    query.bindValue(":nom",nom);
    query.bindValue(":type",type);
    query.bindValue(":quantite",quantite);
    query.bindValue(":etat",etat);
    query.bindValue(":date_acquisition",date_acquisition);


    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du matériel :";
    } else {
        qDebug() << "Matériel ajouté avec succès.";
    }
}
QSqlQueryModel * Materiel::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from MATERIELS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MATERIEL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_ACQUISITION"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
    return model;
}
void Materiel::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("delete from MATERIELS where ID_MATERIEL = :ID");
    query.bindValue(":ID", id);
    query.exec();
}
void Materiel::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE materiels set nom=:nom,type=:type WHERE ID_MATERIEL=:ID_MATERIEL");
    query.bindValue(":ID_MATERIEL",id_materiel);
    query.bindValue(":nom",nom);
    query.bindValue(":type",type);
    query.exec();
}
QSqlQueryModel * Materiel::tri1()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from MATERIELS ORDER BY QUANTITE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MATERIEL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_ACQUISITION"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
    return model;
}
QSqlQueryModel * Materiel::tri2()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from MATERIELS ORDER BY DATE_ACQUISITION ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MATERIEL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_ACQUISITION"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
    return model;
}
QSqlQueryModel * Materiel::tri3()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from MATERIELS ORDER BY TYPE ASC");//DESC
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MATERIEL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_ACQUISITION"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
    return model;
}
QSqlQueryModel * Materiel::rechercher(QString id)
{
    QSqlQueryModel* model = new QSqlQueryModel();

       // Prepare the query using QSqlQuery
       QSqlQuery query;
       query.prepare("SELECT * FROM MATERIELS WHERE ID_MATERIEL = :id");
       query.bindValue(":id", id);
       if (!query.exec()) {
           qDebug() << "Query execution failed:" ;
           delete model; // Clean up if the query fails
           return nullptr;
       }
       model->setQuery(query);

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MATERIEL"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_ACQUISITION"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
    return model;
}
QSqlQueryModel * Materiel::rechercher1(QString type)
{
    QSqlQueryModel* model = new QSqlQueryModel();

       // Prepare the query using QSqlQuery
       QSqlQuery query;
       query.prepare("SELECT * FROM MATERIELS WHERE type = :id");
       query.bindValue(":id", type);
       if (!query.exec()) {
           qDebug() << "Query execution failed:" ;
           delete model; // Clean up if the query fails
           return nullptr;
       }
       model->setQuery(query);

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MATERIEL"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_ACQUISITION"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
    return model;
}

QSqlQueryModel * Materiel::rechercher2(QString etat)
{
    QSqlQueryModel* model = new QSqlQueryModel();

       // Prepare the query using QSqlQuery
       QSqlQuery query;
       query.prepare("SELECT * FROM MATERIELS WHERE etat = :id");
       query.bindValue(":id", etat);
       if (!query.exec()) {
           qDebug() << "Query execution failed:" ;
           delete model; // Clean up if the query fails
           return nullptr;
       }
       model->setQuery(query);

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MATERIEL"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_ACQUISITION"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
    return model;
}
