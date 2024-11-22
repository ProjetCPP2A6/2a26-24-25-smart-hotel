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
    void createPDF(int idchambre, const QString& etat, const QString& type, int tarif, const QString& id, const QString& date_debut, const QString& date_fin);
private slots:

    void on_pushButton_Ajouter_clicked();
    void on_comboBox_etat_activated(int index);
    void on_comboBox_type_activated(int index);
    void on_pushButton_Supprimer_clicked();
    void on_pushButton_Annuler_clicked();

    void on_lineEdit_ID_editingFinished();


    void on_pushButton_tri_clicked();

    void on_pushButton_Recherche_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_qrcode_button_clicked();

    void on_tabWidget_currentChanged(); // statistique

    void on_pushButton_SMS_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_exporter_2_clicked(); // exporter

private:
    Ui::MainWindow *ui;
    Chambre CHtmp;
     bool getChambredata(const int &idchambre,QString &etat,QString &type,float &tarif);
     bool loadChambreData(int idchambre); // Nouvelle méthode pour charger les données de la chambre
     void generateQRCode(int id_chambre);


};

#endif // MAINWINDOW_H
