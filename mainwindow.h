#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "reservation.h"
#include "notificationwidget.h"
#include "arduino.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSerialPort>
#include <QByteArray>
#include <QTimer>

namespace Ui {
class MainWindow; // Déclaration de la classe générée par Qt Designer
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void alerte();
    void showNotification(const Notification &notification);

private slots:
    void rafraichirTable();
    void on_comboBox_statut_activated(int index);
    void on_comboBox_type_activated(int index);
    void on_comboBox_mode_activated(int index);
    void on_annuler_clicked();
    void on_supprimer_clicked();
    void oncomboBoxCritere(int index);
    void on_trier_clicked();
    void on_rechercher_clicked();
    void on_exporter_clicked();
    void on_pushButton_statistiques_clicked();
    void on_modifier_clicked();
    void on_ajouter_clicked();
    void on_enregistrer_clicked();

    void readFromArduino(); // Lire les données de l'Arduino
    void updateObstacleStatus(); // Mettre à jour le statut des obstacles

private:
    Ui::MainWindow *ui; // Interface utilisateur générée par Qt Designer
    QSqlDatabase db; // Base de données SQLite
    reservation Rtmp;

    // Gestion de l'Arduino
    Arduino *arduino;  // Objet pour gérer la communication série avec Arduino
    QByteArray dataBuffer;  // Buffer pour stocker les données reçues
    int placesDisponibles=5;  // Nombre de places disponibles initialisé
    int detection_count = 0;  // Déclaration du compteur de détections

    void setupTimer();  // Configurer un timer pour la lecture périodique des données
};

#endif // MAINWINDOW_H
