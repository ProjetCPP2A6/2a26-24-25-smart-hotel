#ifndef CHAMBRE_H
#define CHAMBRE_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Chambre
{
   private:
       int idchambre;
       float tarif;
       QString etat,type;
public:

    Chambre();
    Chambre(int idchambre,QString etat,QString type,float tarif );


    QString getetat(){return etat ;}
    QString gettype(){return type ;}
    int getidchambre(){return idchambre;}
    float gettarif(){return tarif;}


    void setetat(QString e){etat =e;}
    void settype(QString ty){type = ty;}
    void setidchambre (int idchambre ){this->idchambre=idchambre;}
    void settarif (float tarif ){this->tarif=tarif;}

        // fonctionnalites de base relatives a l'entite chambre
    bool ajouter ();
    bool supprimer(int idchambre);
    QSqlQueryModel * afficher();
    bool modifier(int idchambre, QString etat, QString type, float  tarif);



};

#endif // CHAMBRE_H
