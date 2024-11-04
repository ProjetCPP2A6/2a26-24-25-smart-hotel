#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class employe {
public:

    int id_Employe;
    QString nom;
    QString prenom;
    QString poste;
    QDate date_embauche;
    double salaire;


    employe(int id_Employe, QString nom, QString prenom, QString poste, QDate date_embauche, double salaire);


    int getIdEmploye();
    QString getNom();
    QString getPrenom();
    QString getPoste();
    QDate getDateEmbauche();
    double getSalaire();


    void setIdEmploye(int id_Employe);
    void setNom(QString nom);
    void setPrenom(QString prenom);
    void setPoste(QString poste);
    void setDateEmbauche(QDate date_embauche);
    void setSalaire(double salaire);


    bool addEmployeToDB();
    QSqlQueryModel* fetchAllEmployes();
    bool deleteEmployeFromDB(int id_Employe);
    bool editEmployeInDB(int id_Employe, QString newNom, QString newPrenom, QString newPoste, QDate newDateEmbauche, double newSalaire);
};

#endif // EMPLOYE_H
