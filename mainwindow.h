#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"reservation.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "notificationwidget.h"
#include "arduino.h"
namespace Ui {
class MainWindow;  // Déclaration de la classe générée par Qt Designer
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void alerte();
    void showNotification(const Notification &notification) ;
private slots:
    //void enregistrerReservation();
    /*void supprimerReservation();*/
    //void annulerModification();
    void rafraichirTable();

    void on_comboBox_statut_activated(int index);
    void on_comboBox_type_activated(int index);
    void on_comboBox_mode_activated(int index);
    void on_annuler_clicked();
    void readFromArduino ();
    /*void on_enregistrer_clicked();*/
    void on_supprimer_clicked();

     void oncomboBoxCritere(int index);

    void on_trier_clicked();

     void on_rechercher_clicked();

    void on_exporter_clicked();
     void on_pushButton_statistiques_clicked();  // Slot pour le bouton statistiques





     void on_modifier_clicked();

     void on_ajouter_clicked();

     void on_enregistrer_clicked();

 private:
    Ui::MainWindow *ui;  // Pointeur vers l'interface générée par Qt Designer
    QSqlDatabase db;  // Base de données SQLite

    reservation Rtmp;
    void setupTimer();
    Arduino arduino;
    int placesDisponibles=5;
    void updateObstacleStatus();  // Méthode pour mettre à jour le statut des obstacles

};

#endif // MAINWINDOW_H

