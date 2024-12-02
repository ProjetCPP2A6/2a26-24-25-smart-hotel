/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *statistique;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *id_reservation;
    QLineEdit *id_client;
    QLineEdit *Np;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *Montant;
    QComboBox *comboBox_type;
    QComboBox *comboBox_statut;
    QComboBox *comboBox_mode;
    QPushButton *enregistrer;
    QDateEdit *date_debut;
    QDateEdit *date_fin;
    QPushButton *modifier;
    QPushButton *ajouter;
    QLabel *label_20;
    QTableView *tableView;
    QPushButton *rechercher;
    QLabel *label_21;
    QComboBox *comboBoxCritere;
    QPushButton *trier;
    QLineEdit *lineEdit_idReservation;
    QPushButton *supprimer;
    QPushButton *exporter;
    QPushButton *annuler;
    QWidget *tab_2;
    QPushButton *pushButton_statistiques;
    QLabel *label_type;
    QWidget *graphWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1462, 745);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        statistique = new QTabWidget(centralWidget);
        statistique->setObjectName("statistique");
        statistique->setGeometry(QRect(110, 40, 1191, 641));
        tab = new QWidget();
        tab->setObjectName("tab");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 60, 451, 691));
        groupBox->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 207, 249);"));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 171, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 141, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 100, 161, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 130, 151, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 160, 101, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 190, 151, 20));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 220, 63, 20));
        id_reservation = new QLineEdit(groupBox);
        id_reservation->setObjectName("id_reservation");
        id_reservation->setGeometry(QRect(190, 30, 113, 26));
        id_client = new QLineEdit(groupBox);
        id_client->setObjectName("id_client");
        id_client->setGeometry(QRect(190, 60, 113, 26));
        Np = new QLineEdit(groupBox);
        Np->setObjectName("Np");
        Np->setGeometry(QRect(190, 190, 113, 26));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 350, 171, 20));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 380, 171, 20));
        Montant = new QLineEdit(groupBox);
        Montant->setObjectName("Montant");
        Montant->setGeometry(QRect(170, 340, 113, 26));
        comboBox_type = new QComboBox(groupBox);
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->setObjectName("comboBox_type");
        comboBox_type->setGeometry(QRect(190, 100, 111, 26));
        comboBox_statut = new QComboBox(groupBox);
        comboBox_statut->addItem(QString());
        comboBox_statut->addItem(QString());
        comboBox_statut->addItem(QString());
        comboBox_statut->setObjectName("comboBox_statut");
        comboBox_statut->setGeometry(QRect(190, 220, 111, 26));
        comboBox_mode = new QComboBox(groupBox);
        comboBox_mode->addItem(QString());
        comboBox_mode->addItem(QString());
        comboBox_mode->addItem(QString());
        comboBox_mode->setObjectName("comboBox_mode");
        comboBox_mode->setGeometry(QRect(170, 380, 111, 26));
        enregistrer = new QPushButton(groupBox);
        enregistrer->setObjectName("enregistrer");
        enregistrer->setGeometry(QRect(190, 500, 93, 29));
        date_debut = new QDateEdit(groupBox);
        date_debut->setObjectName("date_debut");
        date_debut->setGeometry(QRect(190, 130, 110, 26));
        date_fin = new QDateEdit(groupBox);
        date_fin->setObjectName("date_fin");
        date_fin->setGeometry(QRect(190, 160, 110, 26));
        modifier = new QPushButton(groupBox);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(330, 460, 93, 29));
        ajouter = new QPushButton(groupBox);
        ajouter->setObjectName("ajouter");
        ajouter->setGeometry(QRect(60, 460, 93, 29));
        label_20 = new QLabel(tab);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(530, 30, 131, 21));
        tableView = new QTableView(tab);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(530, 110, 521, 401));
        rechercher = new QPushButton(tab);
        rechercher->setObjectName("rechercher");
        rechercher->setGeometry(QRect(960, 40, 93, 29));
        label_21 = new QLabel(tab);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(580, 80, 71, 21));
        comboBoxCritere = new QComboBox(tab);
        comboBoxCritere->addItem(QString());
        comboBoxCritere->addItem(QString());
        comboBoxCritere->addItem(QString());
        comboBoxCritere->setObjectName("comboBoxCritere");
        comboBoxCritere->setGeometry(QRect(730, 70, 121, 26));
        trier = new QPushButton(tab);
        trier->setObjectName("trier");
        trier->setGeometry(QRect(960, 70, 93, 29));
        lineEdit_idReservation = new QLineEdit(tab);
        lineEdit_idReservation->setObjectName("lineEdit_idReservation");
        lineEdit_idReservation->setGeometry(QRect(730, 20, 113, 26));
        supprimer = new QPushButton(tab);
        supprimer->setObjectName("supprimer");
        supprimer->setGeometry(QRect(960, 10, 93, 29));
        exporter = new QPushButton(tab);
        exporter->setObjectName("exporter");
        exporter->setGeometry(QRect(920, 540, 111, 29));
        annuler = new QPushButton(tab);
        annuler->setObjectName("annuler");
        annuler->setGeometry(QRect(570, 540, 93, 29));
        statistique->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        pushButton_statistiques = new QPushButton(tab_2);
        pushButton_statistiques->setObjectName("pushButton_statistiques");
        pushButton_statistiques->setGeometry(QRect(110, 280, 93, 29));
        label_type = new QLabel(tab_2);
        label_type->setObjectName("label_type");
        label_type->setGeometry(QRect(450, 50, 63, 20));
        graphWidget = new QWidget(tab_2);
        graphWidget->setObjectName("graphWidget");
        graphWidget->setGeometry(QRect(410, 120, 381, 181));
        statistique->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1462, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        statistique->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Ajouter r\303\251servation", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">Id de la r\303\251servation</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Id du client ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "type de la r\303\251servation ", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Date de d\303\251but", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Date de fin", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Nombre de personnes", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Montant total", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Mode de paiment", nullptr));
        comboBox_type->setItemText(0, QCoreApplication::translate("MainWindow", "Chambre", nullptr));
        comboBox_type->setItemText(1, QCoreApplication::translate("MainWindow", "Restaurant", nullptr));
        comboBox_type->setItemText(2, QCoreApplication::translate("MainWindow", "Parking", nullptr));

        comboBox_statut->setItemText(0, QCoreApplication::translate("MainWindow", "confirm\303\251e", nullptr));
        comboBox_statut->setItemText(1, QCoreApplication::translate("MainWindow", " en attente", nullptr));
        comboBox_statut->setItemText(2, QCoreApplication::translate("MainWindow", "annul\303\251e", nullptr));

        comboBox_mode->setItemText(0, QCoreApplication::translate("MainWindow", "carte bancaire", nullptr));
        comboBox_mode->setItemText(1, QCoreApplication::translate("MainWindow", "esp\303\251ces", nullptr));
        comboBox_mode->setItemText(2, QCoreApplication::translate("MainWindow", "Virement", nullptr));

        enregistrer->setText(QCoreApplication::translate("MainWindow", "enregistrer", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        ajouter->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Id de la reservation", nullptr));
        rechercher->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Trier par:", nullptr));
        comboBoxCritere->setItemText(0, QCoreApplication::translate("MainWindow", "Montant", nullptr));
        comboBoxCritere->setItemText(1, QCoreApplication::translate("MainWindow", "statut", nullptr));
        comboBoxCritere->setItemText(2, QCoreApplication::translate("MainWindow", "date_debut", nullptr));

        trier->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        supprimer->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        exporter->setText(QCoreApplication::translate("MainWindow", "exporter", nullptr));
        annuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        statistique->setTabText(statistique->indexOf(tab), QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_statistiques->setText(QCoreApplication::translate("MainWindow", "statistiques", nullptr));
        label_type->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        statistique->setTabText(statistique->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
