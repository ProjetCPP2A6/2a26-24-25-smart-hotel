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

//#include "arduino.h"

#include "reservation.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSerialPort>
#include <QByteArray>
#include <QTimer>

#include "connection.h"

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

    // *****************gs reservation ************************
    void alerte();
    //void showNotification(const Notification &notification);
private slots:

    void on_pushButton_Ajouter_clicked();
    void on_comboBox_etat_activated(int index);
    void on_comboBox_type_activated(int index);
    void on_pushButton_Supprimer_clicked();
    void on_pushButton_Annuler_clicked();

    void on_lineEdit_ID_editingFinished();

    //void readDataFromArduino();
    void on_pushButton_tri_clicked();

    void on_pushButton_Recherche_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_qrcode_button_clicked();

    void on_tabWidget_currentChanged(); // statistique

    void on_pushButton_SMS_clicked();

   // void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_exporter_2_clicked(); // exporter

    //void update_label();  // Déclaration du slot

     //************************ gs_reservation ****************************************

     void rafraichirTable();
     void on_comboBox_statut_activated(int index);
     void on_comboBox_type_2_activated(int index);
     void on_comboBox_mode_activated(int index);
     void on_annuler_clicked();
     void on_supprimer_clicked();
     //void oncomboBoxCritere(int index);
     void on_trier_clicked();
     void on_rechercher_clicked();
     void on_exporter_clicked();
     void on_pushButton_statistiques_clicked();
     void on_modifier_clicked();
     void on_ajouter_clicked();
     void on_enregistrer_clicked();








     void on_comboBoxCritere_activated(int index);

     //void on_tableView_2_activated(const QModelIndex &index);

     void on_comboBox_criteria_activated(int index);

 private:
    Ui::MainWindow *ui;
    Chambre CHtmp;
    Connection connection;  // Déclare Connection ici

    QSqlDatabase db; // Base de données SQLite
    reservation Rtmp;


     bool getChambredata(const int &idchambre,QString &etat,QString &type,float &tarif);
     bool loadChambreData(int idchambre); // Nouvelle méthode pour charger les données de la chambre
     void generateQRCode(int id_chambre);
    QByteArray data;
     //Arduino A;


};

#endif // MAINWINDOW_H
