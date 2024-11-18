#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include<QtMultimedia>
#include<QStyle>
#include <QFileDialog>
#include "financier.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void clearFields();

private slots:
    void onLoginButtonClicked();
    void showPage1();
    void showPage2();
    void showPage3();
    void showPage4();
    void showPage5();
    void showPage6();
    void showPage7();
    void on_addButton_clicked();




    void on_tableView_6_activated(const QModelIndex &index);

    void on_modifier_button_clicked();

    void on_tri_clicked();



    void on_PDF_clicked();


    void on_pushButton_3_clicked();

    void on_statistique_clicked();

    void on_pushButton_delete_clicked();

    void on_play_button_clicked();

    void on_pause_button_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    financier ETMP;
    financier f;
    QMediaPlayer *M_PLAYER;
    bool validateLogin(const QString &username, const QString &password);
    QStackedWidget *stackedWidget;
    QPushButton *buttons[30];
};

#endif
