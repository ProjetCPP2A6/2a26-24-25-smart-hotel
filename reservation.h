#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class reservation
{
private:
    int id_reservation;
    int id_client;
    QString type_reservation;
    QDate date_debut;
    QDate date_fin;
    int nb_personnes;
    QString statut;
    QString mode_paiement;
    double montant;
    int numt;

public:

    // Constructeurs
    reservation();
    reservation(int id_reservation, int id_client, QString type_reservation,
                QDate date_debut, QDate date_fin, int nb_personnes, QString statut,
                QString mode_paiement ,double montant , int numt);

    // Méthodes
    bool ajouter1();
    bool supprimer1(int id_reservation);
    bool modifier1(int id_reservation, int id_client, QString type_reservation,QDate date_debut, QDate date_fin, int nb_personnes, QString statut,QString mode_paiement ,double montant , int numt);  // Modifier une réservation
    QSqlQueryModel* afficher1();
    bool exporterPDF(const QString &filePath) ;

    // Getters
    int getId_Reservation() {return id_reservation ;}
    int getId_Client() {return id_client ;}
    QString getType_Reservation() {return type_reservation ;}
    QDate getDate_Debut() {return date_debut ;}
    QDate getDate_Fin(){return date_fin ;}
    int getNb_Personnes(){return nb_personnes ;}
    QString getStatut(){return statut ;}
    double getMontant() {return montant ;}
    QString getMode_Paiement(){return mode_paiement ;}
    int getnumT (){return numt ;}


    // Setters
    void setId_Reservation(int idR) {id_reservation = idR;}
    void setId_Client(int idC){id_client=idC;}
    void setType_Reservation(QString typeR){type_reservation=typeR;}
    void setDate_Debut( QDate dateD){date_debut=dateD;}
    void setDate_Fin(QDate dateF){date_fin=dateF;}
    void setNb_Personnes(int nb){nb_personnes=nb;}
    void setStatut( QString stat){statut=stat;}
    void setMode_Paiement( QString mode){mode_paiement=mode;}
    void setMontant(double mont){montant=mont;}
    void setnumT ( int num){numt=num;}

};

#endif // RESERVATION_H



