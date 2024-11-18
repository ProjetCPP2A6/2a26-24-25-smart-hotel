#ifndef SERVICE_H
#define SERVICE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class service {
public:
    // Member variables
    int id_service; // Changed to match database column name
    QString nom_service; // Changed to match database column name
    QString etat;
    QString categorie;
    int cout; // Changed type from double to int as per your requirements

    // Constructor
    service(int id_service, QString nom_service, QString etat, QString categorie, int cout);

    // Getters
    int getIdService();
    QString getNomService();
    QString getEtat();
    QString getCategorie();
    int getCout();

    // Setters
    void setIdService(int id_service);
    void setNomService(QString nom_service);
    void setEtat(QString etat);
    void setCategorie(QString categorie);
    void setCout(int cout);

    // Database functionalities
    bool addServiceToDB();
    QSqlQueryModel* fetchAllServices();
    bool deleteServiceFromDB(int id_service);
    bool editServiceInDB(int id_service, QString newEtat, double newCout);
    void refreshServiceList();
    QSqlQueryModel* displayAllServices();
};

#endif // SERVICE_H
