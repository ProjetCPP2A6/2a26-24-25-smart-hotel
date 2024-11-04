#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Chambre.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_Ajouter_clicked();
    void on_comboBox_etat_activated(int index);
    void on_comboBox_type_activated(int index);

    void on_pushButton_Supprimer_clicked();

    void on_pushButton_Modifier_clicked();

    void on_comboBox_etat_2_activated(int index);

    void on_comboBox_type_2_activated(int index);

    void on_pushButton_SaveModifier_clicked();

    void on_pushButton_Annuler_clicked();

    void on_pushButton_Annuler2_clicked();

    void on_lineEdit_Modifier_editingFinished();

    void on_pushButton_Annuler_3_clicked();

private:
    Ui::MainWindow *ui;
    Chambre CHtmp;
     bool getChambredata(const int &idchambre,QString &etat,QString &type,int &tarif);
};

#endif // MAINWINDOW_H
