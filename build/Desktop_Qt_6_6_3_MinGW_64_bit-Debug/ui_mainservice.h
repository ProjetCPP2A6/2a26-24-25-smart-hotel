/********************************************************************************
** Form generated from reading UI file 'mainservice.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSERVICE_H
#define UI_MAINSERVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainservice
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_6;
    QLineEdit *lineEdit_sr;
    QLabel *label;
    QPushButton *pushButton_afficher;
    QTableWidget *tableWidget;
    QWidget *tab_3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_id;
    QLineEdit *lineEdit_nom;
    QLineEdit *lineEdit_etat;
    QLineEdit *lineEdit_categorie;
    QLineEdit *lineEdit_cout;
    QPushButton *pushButton_ajouter;
    QWidget *tab_4;
    QLabel *label_7;
    QLineEdit *lineEdit_id_ed;
    QLabel *label_8;
    QLineEdit *lineEdit__etat_ed;
    QLineEdit *lineEdit_cout_ed;
    QLabel *label_10;
    QPushButton *pushButton_edit;
    QWidget *tab_5;
    QLabel *label_9;
    QLineEdit *lineEdit_idSP;
    QPushButton *pushButton_supprimer;
    QWidget *tab;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton_display;
    QPushButton *pushButton_exportpdf;
    QPushButton *pushButton_Stat;
    QTableView *tableView_stat;
    QWidget *tab_2;
    QPushButton *DeliveryConfirmation;
    QPushButton *btnRoomCleaned;
    QPushButton *InventoryAlert;
    QPushButton *DealsPromotions;
    QPushButton *DealsPromotions_2;
    QPushButton *ShiftNotifications;
    QLineEdit *lineEdit_subject;
    QLineEdit *lineEdit_recipient;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QPushButton *pushButton_sendEmail;
    QTextEdit *textEdit;
    QWidget *tab_7;
    QCalendarWidget *calendarWidget;
    QLineEdit *lineEdit_eventName;
    QTextEdit *textEdit_description;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *lineEdit_search;
    QPushButton *searchevent;
    QTextEdit *textEdit_eventDetails;
    QLabel *label_18;
    QPushButton *AddEvent;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainservice)
    {
        if (mainservice->objectName().isEmpty())
            mainservice->setObjectName("mainservice");
        mainservice->resize(1164, 647);
        centralwidget = new QWidget(mainservice);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(30, 20, 1121, 591));
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        lineEdit_sr = new QLineEdit(tab_6);
        lineEdit_sr->setObjectName("lineEdit_sr");
        lineEdit_sr->setGeometry(QRect(250, 40, 221, 28));
        label = new QLabel(tab_6);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 40, 121, 21));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(5);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        label->setFont(font);
        pushButton_afficher = new QPushButton(tab_6);
        pushButton_afficher->setObjectName("pushButton_afficher");
        pushButton_afficher->setGeometry(QRect(560, 40, 121, 31));
        tableWidget = new QTableWidget(tab_6);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(60, 150, 631, 271));
        tabWidget->addTab(tab_6, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_2 = new QLabel(tab_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 50, 121, 21));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);
        label_3 = new QLabel(tab_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 110, 141, 21));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);
        label_4 = new QLabel(tab_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 160, 121, 21));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font);
        label_5 = new QLabel(tab_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 230, 121, 21));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setFont(font);
        label_6 = new QLabel(tab_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(70, 300, 121, 21));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setFont(font);
        lineEdit_id = new QLineEdit(tab_3);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setGeometry(QRect(300, 50, 221, 28));
        lineEdit_nom = new QLineEdit(tab_3);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(300, 110, 221, 28));
        lineEdit_etat = new QLineEdit(tab_3);
        lineEdit_etat->setObjectName("lineEdit_etat");
        lineEdit_etat->setGeometry(QRect(300, 160, 221, 28));
        lineEdit_categorie = new QLineEdit(tab_3);
        lineEdit_categorie->setObjectName("lineEdit_categorie");
        lineEdit_categorie->setGeometry(QRect(300, 230, 221, 28));
        lineEdit_cout = new QLineEdit(tab_3);
        lineEdit_cout->setObjectName("lineEdit_cout");
        lineEdit_cout->setGeometry(QRect(300, 300, 221, 28));
        pushButton_ajouter = new QPushButton(tab_3);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(640, 400, 86, 29));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        label_7 = new QLabel(tab_4);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(160, 60, 121, 21));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setFont(font);
        lineEdit_id_ed = new QLineEdit(tab_4);
        lineEdit_id_ed->setObjectName("lineEdit_id_ed");
        lineEdit_id_ed->setGeometry(QRect(360, 60, 221, 28));
        label_8 = new QLabel(tab_4);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(70, 160, 121, 21));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setFont(font);
        lineEdit__etat_ed = new QLineEdit(tab_4);
        lineEdit__etat_ed->setObjectName("lineEdit__etat_ed");
        lineEdit__etat_ed->setGeometry(QRect(280, 160, 221, 28));
        lineEdit_cout_ed = new QLineEdit(tab_4);
        lineEdit_cout_ed->setObjectName("lineEdit_cout_ed");
        lineEdit_cout_ed->setGeometry(QRect(280, 270, 221, 28));
        label_10 = new QLabel(tab_4);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(70, 270, 121, 21));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setFont(font);
        pushButton_edit = new QPushButton(tab_4);
        pushButton_edit->setObjectName("pushButton_edit");
        pushButton_edit->setGeometry(QRect(590, 200, 121, 31));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        label_9 = new QLabel(tab_5);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(170, 140, 121, 21));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setFont(font);
        lineEdit_idSP = new QLineEdit(tab_5);
        lineEdit_idSP->setObjectName("lineEdit_idSP");
        lineEdit_idSP->setGeometry(QRect(370, 140, 221, 28));
        pushButton_supprimer = new QPushButton(tab_5);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(330, 280, 121, 31));
        tabWidget->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        tableWidget_2 = new QTableWidget(tab);
        if (tableWidget_2->columnCount() < 5)
            tableWidget_2->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(20, 40, 631, 271));
        pushButton_display = new QPushButton(tab);
        pushButton_display->setObjectName("pushButton_display");
        pushButton_display->setGeometry(QRect(90, 360, 121, 31));
        pushButton_exportpdf = new QPushButton(tab);
        pushButton_exportpdf->setObjectName("pushButton_exportpdf");
        pushButton_exportpdf->setGeometry(QRect(370, 360, 121, 31));
        pushButton_Stat = new QPushButton(tab);
        pushButton_Stat->setObjectName("pushButton_Stat");
        pushButton_Stat->setGeometry(QRect(830, 50, 121, 31));
        tableView_stat = new QTableView(tab);
        tableView_stat->setObjectName("tableView_stat");
        tableView_stat->setGeometry(QRect(700, 120, 381, 211));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        DeliveryConfirmation = new QPushButton(tab_2);
        DeliveryConfirmation->setObjectName("DeliveryConfirmation");
        DeliveryConfirmation->setGeometry(QRect(942, 20, 161, 29));
        btnRoomCleaned = new QPushButton(tab_2);
        btnRoomCleaned->setObjectName("btnRoomCleaned");
        btnRoomCleaned->setGeometry(QRect(10, 20, 131, 29));
        InventoryAlert = new QPushButton(tab_2);
        InventoryAlert->setObjectName("InventoryAlert");
        InventoryAlert->setGeometry(QRect(770, 20, 141, 29));
        DealsPromotions = new QPushButton(tab_2);
        DealsPromotions->setObjectName("DealsPromotions");
        DealsPromotions->setGeometry(QRect(190, 20, 131, 29));
        DealsPromotions_2 = new QPushButton(tab_2);
        DealsPromotions_2->setObjectName("DealsPromotions_2");
        DealsPromotions_2->setGeometry(QRect(570, 20, 131, 29));
        ShiftNotifications = new QPushButton(tab_2);
        ShiftNotifications->setObjectName("ShiftNotifications");
        ShiftNotifications->setGeometry(QRect(370, 20, 141, 29));
        lineEdit_subject = new QLineEdit(tab_2);
        lineEdit_subject->setObjectName("lineEdit_subject");
        lineEdit_subject->setGeometry(QRect(340, 160, 431, 31));
        lineEdit_recipient = new QLineEdit(tab_2);
        lineEdit_recipient->setObjectName("lineEdit_recipient");
        lineEdit_recipient->setGeometry(QRect(340, 100, 431, 28));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(240, 100, 91, 21));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setFont(font);
        label_12 = new QLabel(tab_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(240, 170, 71, 21));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setFont(font);
        label_13 = new QLabel(tab_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(240, 220, 61, 21));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        label_13->setFont(font);
        pushButton_sendEmail = new QPushButton(tab_2);
        pushButton_sendEmail->setObjectName("pushButton_sendEmail");
        pushButton_sendEmail->setGeometry(QRect(930, 450, 83, 29));
        textEdit = new QTextEdit(tab_2);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(340, 230, 431, 271));
        tabWidget->addTab(tab_2, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        calendarWidget = new QCalendarWidget(tab_7);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(10, 10, 581, 521));
        lineEdit_eventName = new QLineEdit(tab_7);
        lineEdit_eventName->setObjectName("lineEdit_eventName");
        lineEdit_eventName->setGeometry(QRect(730, 40, 221, 28));
        textEdit_description = new QTextEdit(tab_7);
        textEdit_description->setObjectName("textEdit_description");
        textEdit_description->setGeometry(QRect(730, 90, 221, 131));
        label_14 = new QLabel(tab_7);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(780, 10, 121, 21));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        label_14->setFont(font);
        label_15 = new QLabel(tab_7);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(600, 40, 121, 21));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setFont(font);
        label_16 = new QLabel(tab_7);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(600, 130, 121, 21));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setFont(font);
        label_17 = new QLabel(tab_7);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(780, 230, 121, 21));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        label_17->setFont(font);
        lineEdit_search = new QLineEdit(tab_7);
        lineEdit_search->setObjectName("lineEdit_search");
        lineEdit_search->setGeometry(QRect(640, 270, 221, 28));
        searchevent = new QPushButton(tab_7);
        searchevent->setObjectName("searchevent");
        searchevent->setGeometry(QRect(890, 270, 121, 31));
        textEdit_eventDetails = new QTextEdit(tab_7);
        textEdit_eventDetails->setObjectName("textEdit_eventDetails");
        textEdit_eventDetails->setGeometry(QRect(670, 350, 351, 181));
        label_18 = new QLabel(tab_7);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(810, 320, 61, 21));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setFont(font);
        AddEvent = new QPushButton(tab_7);
        AddEvent->setObjectName("AddEvent");
        AddEvent->setGeometry(QRect(990, 110, 83, 29));
        tabWidget->addTab(tab_7, QString());
        mainservice->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(mainservice);
        statusbar->setObjectName("statusbar");
        mainservice->setStatusBar(statusbar);

        retranslateUi(mainservice);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(mainservice);
    } // setupUi

    void retranslateUi(QMainWindow *mainservice)
    {
        mainservice->setWindowTitle(QCoreApplication::translate("mainservice", "mainservice", nullptr));
        label->setText(QCoreApplication::translate("mainservice", "Serivce ID :", nullptr));
        pushButton_afficher->setText(QCoreApplication::translate("mainservice", "Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("mainservice", "ID SERVICE", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("mainservice", "NOM SERVICE", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("mainservice", "ETAT", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("mainservice", "CATEGORIE", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("mainservice", "COUT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("mainservice", "Search", nullptr));
        label_2->setText(QCoreApplication::translate("mainservice", "Serivce ID :", nullptr));
        label_3->setText(QCoreApplication::translate("mainservice", "NOM SERVICE :", nullptr));
        label_4->setText(QCoreApplication::translate("mainservice", "ETAT :", nullptr));
        label_5->setText(QCoreApplication::translate("mainservice", "CATEGORIE :", nullptr));
        label_6->setText(QCoreApplication::translate("mainservice", "COUT :", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("mainservice", "ADD", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("mainservice", "Add Service", nullptr));
        label_7->setText(QCoreApplication::translate("mainservice", "Serivce ID :", nullptr));
        label_8->setText(QCoreApplication::translate("mainservice", "ETAT :", nullptr));
        label_10->setText(QCoreApplication::translate("mainservice", "COUT :", nullptr));
        pushButton_edit->setText(QCoreApplication::translate("mainservice", "EDIT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("mainservice", "Edit Service", nullptr));
        label_9->setText(QCoreApplication::translate("mainservice", "Serivce ID :", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("mainservice", "DELETE", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("mainservice", "Delete Service", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("mainservice", "ID SERVICE", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("mainservice", "NOM SERVICE", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("mainservice", "ETAT", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("mainservice", "CATEGORIE", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("mainservice", "COUT", nullptr));
        pushButton_display->setText(QCoreApplication::translate("mainservice", "display", nullptr));
        pushButton_exportpdf->setText(QCoreApplication::translate("mainservice", "Export", nullptr));
        pushButton_Stat->setText(QCoreApplication::translate("mainservice", "Stat", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("mainservice", "display", nullptr));
        DeliveryConfirmation->setText(QCoreApplication::translate("mainservice", "Delivery Confirmation", nullptr));
        btnRoomCleaned->setText(QCoreApplication::translate("mainservice", "Room Cleaned", nullptr));
        InventoryAlert->setText(QCoreApplication::translate("mainservice", "Inventory Alert", nullptr));
        DealsPromotions->setText(QCoreApplication::translate("mainservice", "Deals Promotions", nullptr));
        DealsPromotions_2->setText(QCoreApplication::translate("mainservice", "Deals Promotions", nullptr));
        ShiftNotifications->setText(QCoreApplication::translate("mainservice", "Shift Notifications", nullptr));
        label_11->setText(QCoreApplication::translate("mainservice", "Recipients", nullptr));
        label_12->setText(QCoreApplication::translate("mainservice", "Subject", nullptr));
        label_13->setText(QCoreApplication::translate("mainservice", "Body", nullptr));
        pushButton_sendEmail->setText(QCoreApplication::translate("mainservice", "send", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("mainservice", "Email", nullptr));
        label_14->setText(QCoreApplication::translate("mainservice", "Add Event ", nullptr));
        label_15->setText(QCoreApplication::translate("mainservice", "Event Name", nullptr));
        label_16->setText(QCoreApplication::translate("mainservice", "Description", nullptr));
        label_17->setText(QCoreApplication::translate("mainservice", "Search Event ", nullptr));
        searchevent->setText(QCoreApplication::translate("mainservice", "Search", nullptr));
        label_18->setText(QCoreApplication::translate("mainservice", "Event", nullptr));
        AddEvent->setText(QCoreApplication::translate("mainservice", "ADD", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("mainservice", "Task Scheduling", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainservice: public Ui_mainservice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSERVICE_H
