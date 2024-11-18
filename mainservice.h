#ifndef MAINSERVICE_H
#define MAINSERVICE_H

#include <QMainWindow>

#include <QWidget>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMap>
#include <QPair>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui {
class mainservice;
}
QT_END_NAMESPACE

class mainservice : public QMainWindow
{
    Q_OBJECT

public:
    mainservice(QWidget *parent = nullptr);
    ~mainservice();
private:
    QMap<QDate, QPair<QString, QString>> events;  // Declare the events map

    QCalendarWidget *calendarWidget;
    QLineEdit *lineEdit_eventName;
    QTextEdit *textEdit_description;
    QTextEdit *textEdit_eventDetails;
    QLineEdit *lineEdit_search;
    QPushButton *btn_addEvent;
    QPushButton *btn_searchEvent;
private slots:


    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();



    void on_pushButton_afficher_clicked();





    void on_pushButton_edit_clicked();

    void on_pushButton_display_clicked();



    void on_pushButton_sendEmail_clicked();

    void on_btnRoomCleaned_clicked();

    void on_DealsPromotions_clicked();

    void on_ShiftNotifications_clicked();

    void on_DealsPromotions_2_clicked();

    void on_InventoryAlert_clicked();



    void on_DeliveryConfirmation_clicked();

    void on_searchevent_clicked();

    void on_AddEvent_clicked();

    void on_calendarWidget_activated(const QDate &date);

    ;

    void on_pushButton_exportpdf_clicked();

    void on_pushButton_Stat_clicked();

private:
    Ui::mainservice *ui;
};
#endif // MAINSERVICE_H
