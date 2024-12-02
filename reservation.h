#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class reservation
{
public:
    // Constructeur
    reservation(int id_reservation = 0, int id_client = 0, QString type_reservation = "", QDate date_debut = QDate(), QDate date_fin = QDate(),
                int nb_personnes = 0, QString statut = "", double montant = 0.0, QString mode_paiement = "");

    // Méthodes
    bool ajouter();
    bool supprimer(int id);
    bool modifier(int id_reservation);
    QSqlQueryModel* afficher();  // Afficher toutes les réservations
    QSqlQuery trier(QString critere);
   /* bool rechercher(int id_reservation);*/

    QSqlQueryModel* rechercher(const QString& critere, const QString& value);

    bool exporterPDF(const QString &filePath);
    // Getters
    int getIdReservation() const { return id_reservation; }
    int getIdClient() const { return id_client; }
    QString getTypeReservation() const { return type_reservation; }
    QDate getDateDebut() const { return date_debut; }
    QDate getDateFin() const { return date_fin; }
    int getNbPersonnes() const { return nb_personnes; }
    QString getStatut() const { return statut; }
    double getMontant() const { return montant; }
    QString getModePaiement() const { return mode_paiement; }

    // Setters
    void setIdReservation(int id) { id_reservation = id; }
    void setIdClient(int id) { id_client = id; }
    void setTypeReservation(const QString &type) { type_reservation = type; }
    void setDateDebut(const QDate &date) { date_debut = date; }
    void setDateFin(const QDate &date) { date_fin = date; }
    void setNbPersonnes(int nb) { nb_personnes = nb; }
    void setStatut(const QString &stat) { statut = stat; }
    void setMontant(double montant) { this->montant = montant; }
    void setModePaiement(const QString &mode) { mode_paiement = mode; }



private:
    int id_reservation;
    int id_client;
    QString type_reservation;
    QDate date_debut;
    QDate date_fin;
    int nb_personnes;
    QString statut;
    double montant;
    QString mode_paiement;
};

#endif // RESERVATION_H
