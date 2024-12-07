#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Chambre.h"
#include <QMainWindow>

#include <QMainWindow>
#include <QPdfWriter>
#include <QPainter>
#include <QTableView>
#include <QFileDialog>
#include <QMessageBox>

#include "arduino.h"
#include "reservation.h"


#include "financier.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void box();
    void createPDF(int idchambre, const QString& etat, const QString& type, float tarif, const QString& id, const QString& date_debut, const QString& date_fin);
private slots:

    void on_pushButton_Ajouter_clicked();
    void on_comboBox_etat_activated(int index);
    void on_comboBox_type_activated(int index);
    void on_pushButton_Supprimer_clicked();
    void on_pushButton_Annuler_clicked();

    void on_lineEdit_ID_editingFinished();

    void readDataFromArduino();
    void on_pushButton_tri_clicked();

    void on_pushButton_Recherche_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_qrcode_button_clicked();

    void on_tabWidget_currentChanged(); // statistique

    void on_pushButton_SMS_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_exporter_2_clicked(); // exporter

     void update_label();  // Déclaration du slot


     void on_pushButton_Ajouter1_clicked(); // Ajouter une réservation
     void on_pushButton_Modifier1_clicked(); // Modifier une réservation
     void on_pushButton_Supprimer1_clicked(); // Supprimer une réservation
     void on_pushButton_Recherche1_clicked();
     void on_pushButton_Annuler1_clicked();


     void on_lineEdit_IDReservation_editingFinished();
     void on_tabWidget_currentChanged1();
     void on_tableView_2_clicked(const QModelIndex &index);

     void on_pushButton_tri1_2_clicked();
     void clearFields1();
      void clearFields3();

     void on_pushButton_exporterela_clicked();

     void on_pushButton_Ajouter3_clicked();

     void on_pushButton_2_clicked();

     void on_pushButton_modifiertr_clicked();

     void on_pushButton_6_clicked();

     void on_pushButton_historique_clicked();



     void on_pushButton_3_clicked();

     void on_pushButton_supt_clicked();

     void on_pushButton_recherchetr_clicked();

     void on_tableView_3_activated(const QModelIndex &index);

     void on_tableView_trr_activated(const QModelIndex &index);

     void on_tabWidget_2_currentChanged();

 private:
    Ui::MainWindow *ui;
    Chambre CHtmp;
     bool getChambredata(const int &idchambre,QString &etat,QString &type,float &tarif);
     bool loadChambreData(int idchambre); // Nouvelle méthode pour charger les données de la chambre
     void generateQRCode(int id_chambre);

     QByteArray data;
     Arduino A;

     bool loadReservationData(int id_reservation);
     bool getReservationData(const int &id_reservation, int &id_client, QString &type_reservation, QDate &date_debut, QDate &date_fin, int &nb_personnes, QString &statut, QString &mode_paiement, double &montant, int &numt);
     reservation resTmp;

     financier ETMP;
     financier f;
};

#endif // MAINWINDOW_H
