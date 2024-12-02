#ifndef MATERIEL_H
#define MATERIEL_H
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QString>
#include <QDate>
class Materiel {
private:
    int id_materiel;
    QString nom;
    QString type;
    int quantite;
    QString etat;
    QDate date_acquisition;
    int id_employe;

public:

    Materiel();
    Materiel(int id_materiel, QString nom, QString type, int quantite,
             QString etat, QDate date_acquisition);
    Materiel(int id_materiel, QString nom, QString type);

    int getIdMateriel() const;
    void setIdMateriel(int id_materiel);

    std::string getNom() const;
    void setNom(const std::string& nom);

    std::string getType() const;
    void setType(const std::string& type);

    int getQuantite() const;
    void setQuantite(int quantite);

    std::string getEtat() const;
    void setEtat(const std::string& etat);

    std::string getDateAcquisition() const;
    void setDateAcquisition(const std::string& date_acquisition);

    int getIdEmploye() const;
    void setIdEmploye(int id_employe);


    void ajouterMateriel();
    void supprimer(int id);
    void modifier();
    QSqlQueryModel *afficher();
    QSqlQueryModel *tri1();
    QSqlQueryModel *tri2();
    QSqlQueryModel *tri3();
    QSqlQueryModel * rechercher(QString id);
    QSqlQueryModel * rechercher1(QString id);
    QSqlQueryModel * rechercher2(QString id);
};

#endif // MATERIEL_H

