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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainservice)
    {
        if (mainservice->objectName().isEmpty())
            mainservice->setObjectName("mainservice");
        mainservice->resize(800, 600);
        centralwidget = new QWidget(mainservice);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 20, 771, 521));
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
        mainservice->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(mainservice);
        statusbar->setObjectName("statusbar");
        mainservice->setStatusBar(statusbar);

        retranslateUi(mainservice);

        tabWidget->setCurrentIndex(2);


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
    } // retranslateUi

};

namespace Ui {
    class mainservice: public Ui_mainservice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSERVICE_H
