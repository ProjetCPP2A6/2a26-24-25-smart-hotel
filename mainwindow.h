#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<arduino.h>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool insertImageIntoDatabase(const QByteArray& imageData,QString ID);
    void handleArduinoData();
private slots:
    void on_ajouterMateriel_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_ajouterMateriel_2_clicked();

    void on_arduinoafficher_clicked();

    void on_closearduino_clicked();



private:
    Ui::MainWindow *ui;

    void initarduinoConnection() ;
    void onDataReceived();

    Arduino A;
    QByteArray data;
};
#endif // MAINWINDOW_H
