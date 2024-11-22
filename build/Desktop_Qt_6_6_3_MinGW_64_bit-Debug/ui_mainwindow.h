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
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label_5;
    QLineEdit *lineEdit_ID;
    QLabel *label_6;
    QComboBox *comboBox_etat;
    QLabel *label_7;
    QComboBox *comboBox_type;
    QLabel *label_8;
    QLineEdit *lineEdit_T;
    QPushButton *pushButton_Ajouter;
    QPushButton *pushButton_Annuler;
    QTableView *tableView;
    QLineEdit *lineEdit_Rech;
    QPushButton *pushButton_Recherche;
    QPushButton *pushButton_Supprimer;
    QLabel *label_17;
    QComboBox *comboBox_trier;
    QPushButton *pushButton_tri;
    QPushButton *qrcode_button;
    QLabel *qr_code;
    QPushButton *pushButton_SMS;
    QComboBox *comboBox_trier_2;
    QPushButton *pushButton_exporter_2;
    QComboBox *comboBox;
    QLabel *label;
    QWidget *tab_4;
    QLabel *label_type;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1429, 878);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1381, 651));
        tabWidget->setMaximumSize(QSize(1920, 1680));
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));
        tab = new QWidget();
        tab->setObjectName("tab");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 20, 291, 541));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 174, 161);"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 30, 111, 20));
        label_5->setStyleSheet(QString::fromUtf8(""));
        lineEdit_ID = new QLineEdit(groupBox);
        lineEdit_ID->setObjectName("lineEdit_ID");
        lineEdit_ID->setGeometry(QRect(20, 60, 181, 31));
        lineEdit_ID->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 100, 141, 20));
        label_6->setStyleSheet(QString::fromUtf8(""));
        comboBox_etat = new QComboBox(groupBox);
        comboBox_etat->addItem(QString());
        comboBox_etat->addItem(QString());
        comboBox_etat->setObjectName("comboBox_etat");
        comboBox_etat->setGeometry(QRect(20, 140, 181, 31));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 190, 201, 31));
        label_7->setStyleSheet(QString::fromUtf8(""));
        comboBox_type = new QComboBox(groupBox);
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->setObjectName("comboBox_type");
        comboBox_type->setGeometry(QRect(20, 230, 181, 31));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 280, 141, 31));
        label_8->setStyleSheet(QString::fromUtf8(""));
        lineEdit_T = new QLineEdit(groupBox);
        lineEdit_T->setObjectName("lineEdit_T");
        lineEdit_T->setGeometry(QRect(20, 320, 181, 31));
        lineEdit_T->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_Ajouter = new QPushButton(groupBox);
        pushButton_Ajouter->setObjectName("pushButton_Ajouter");
        pushButton_Ajouter->setGeometry(QRect(10, 420, 111, 41));
        pushButton_Ajouter->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_Annuler = new QPushButton(groupBox);
        pushButton_Annuler->setObjectName("pushButton_Annuler");
        pushButton_Annuler->setGeometry(QRect(150, 420, 111, 41));
        pushButton_Annuler->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tableView = new QTableView(tab);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(390, 190, 501, 251));
        tableView->setStyleSheet(QString::fromUtf8("QTableView {\n"
"    background-color: #f2f2f2; /* Couleur de fond gris clair pour la table enti\303\250re */\n"
"    border: 1px solid #000000; /* Couleur de bordure noire pour la table enti\303\250re */\n"
"    selection-background-color: #cccccc; /* Couleur de fond gris clair pour les cellules s\303\251lectionn\303\251es */\n"
"    color: #000000; /* Couleur du texte en noir */\n"
"    font: bold 14px \"Gill Sans MT\"; /* Police en Gill Sans MT Bold */\n"
"}\n"
"\n"
"/* Style pour les cellules individuelles */\n"
"QTableView::item {\n"
"    padding: 5px; /* Espacement pour le contenu des cellules */\n"
"    background-color: #f2f2f2; /* Couleur de fond gris clair pour les cellules */\n"
"    color: #000000; /* Couleur du texte en noir */\n"
"    border: 1px solid #cccccc; /* Bordure gris clair pour les cellules */\n"
"}\n"
"\n"
"/* Style pour les en-t\303\252tes */\n"
"QHeaderView::section {\n"
"    background-color: #e6e6e6; /* Couleur de fond gris clair pour les sections d'en-t\303\252te */\n"
"    border"
                        ": 1px solid #cccccc; /* Couleur de bordure gris clair pour les sections d'en-t\303\252te */\n"
"    padding: 5px; /* Espacement pour le contenu des sections d'en-t\303\252te */\n"
"    color: #000000; /* Couleur du texte en noir */\n"
"    font: bold 14px \"Gill Sans MT\"; /* Police en Gill Sans MT Bold */\n"
"}\n"
"\n"
"/* Style pour le coin sup\303\251rieur gauche (bouton de coin) */\n"
"QTableCornerButton::section {\n"
"    background-color: #e6e6e6; /* Couleur de fond gris clair pour la section du coin */\n"
"    font: bold 14px \"Gill Sans MT\"; /* Police en Gill Sans MT Bold */\n"
"}\n"
"\n"
"/* Couleur de fond au survol de la cellule */\n"
"QTableView::item:hover {\n"
"    background-color: #d9d9d9; /* Changer la couleur de fond en gris plus fonc\303\251 survol\303\251 */\n"
"}"));
        lineEdit_Rech = new QLineEdit(tab);
        lineEdit_Rech->setObjectName("lineEdit_Rech");
        lineEdit_Rech->setGeometry(QRect(520, 80, 181, 31));
        lineEdit_Rech->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_Recherche = new QPushButton(tab);
        pushButton_Recherche->setObjectName("pushButton_Recherche");
        pushButton_Recherche->setGeometry(QRect(730, 80, 91, 31));
        pushButton_Recherche->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_Supprimer = new QPushButton(tab);
        pushButton_Supprimer->setObjectName("pushButton_Supprimer");
        pushButton_Supprimer->setGeometry(QRect(840, 80, 101, 31));
        pushButton_Supprimer->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_17 = new QLabel(tab);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(380, 150, 121, 21));
        comboBox_trier = new QComboBox(tab);
        comboBox_trier->setObjectName("comboBox_trier");
        comboBox_trier->setGeometry(QRect(520, 140, 181, 31));
        pushButton_tri = new QPushButton(tab);
        pushButton_tri->setObjectName("pushButton_tri");
        pushButton_tri->setGeometry(QRect(730, 140, 71, 31));
        pushButton_tri->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        qrcode_button = new QPushButton(tab);
        qrcode_button->setObjectName("qrcode_button");
        qrcode_button->setGeometry(QRect(1020, 140, 93, 28));
        qr_code = new QLabel(tab);
        qr_code->setObjectName("qr_code");
        qr_code->setGeometry(QRect(900, 180, 361, 381));
        qr_code->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));
        pushButton_SMS = new QPushButton(tab);
        pushButton_SMS->setObjectName("pushButton_SMS");
        pushButton_SMS->setGeometry(QRect(800, 460, 91, 31));
        comboBox_trier_2 = new QComboBox(tab);
        comboBox_trier_2->addItem(QString());
        comboBox_trier_2->addItem(QString());
        comboBox_trier_2->setObjectName("comboBox_trier_2");
        comboBox_trier_2->setGeometry(QRect(380, 80, 131, 31));
        pushButton_exporter_2 = new QPushButton(tab);
        pushButton_exporter_2->setObjectName("pushButton_exporter_2");
        pushButton_exporter_2->setGeometry(QRect(390, 460, 101, 31));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(670, 460, 121, 31));
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(540, 460, 111, 21));
        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        label_type = new QLabel(tab_4);
        label_type->setObjectName("label_type");
        label_type->setGeometry(QRect(180, 40, 691, 441));
        label_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1429, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Ajouter un chambre", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Code:</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Etat_Chambre:</span></p></body></html>", nullptr));
        comboBox_etat->setItemText(0, QCoreApplication::translate("MainWindow", "Occupee", nullptr));
        comboBox_etat->setItemText(1, QCoreApplication::translate("MainWindow", "Disponible", nullptr));

        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Type de chambre :</span></p></body></html>", nullptr));
        comboBox_type->setItemText(0, QCoreApplication::translate("MainWindow", "simple", nullptr));
        comboBox_type->setItemText(1, QCoreApplication::translate("MainWindow", "double", nullptr));
        comboBox_type->setItemText(2, QCoreApplication::translate("MainWindow", "suite", nullptr));
        comboBox_type->setItemText(3, QCoreApplication::translate("MainWindow", "famile", nullptr));

        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Tarif par nuit:</span></p></body></html>", nullptr));
        pushButton_Ajouter->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        pushButton_Annuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        pushButton_Recherche->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        pushButton_Supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Trier par :</span></p></body></html>", nullptr));
        pushButton_tri->setText(QCoreApplication::translate("MainWindow", "Tri", nullptr));
        qrcode_button->setText(QCoreApplication::translate("MainWindow", "QRCode", nullptr));
        qr_code->setText(QString());
        pushButton_SMS->setText(QCoreApplication::translate("MainWindow", "SMS", nullptr));
        comboBox_trier_2->setItemText(0, QCoreApplication::translate("MainWindow", "idchambre", nullptr));
        comboBox_trier_2->setItemText(1, QCoreApplication::translate("MainWindow", "tarif", nullptr));

        pushButton_exporter_2->setText(QCoreApplication::translate("MainWindow", "Exporter pdf", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">id_reservation :</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Aceuille", nullptr));
        label_type->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Fonctionnaliter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
