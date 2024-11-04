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
    QLineEdit *lineEdit_ID;
    QLineEdit *lineEdit_T;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton_Ajouter;
    QComboBox *comboBox_etat;
    QComboBox *comboBox_type;
    QPushButton *pushButton_Annuler;
    QWidget *tab_3;
    QLabel *label_2;
    QPushButton *pushButton_Supprimer;
    QLineEdit *lineEdit_supp;
    QPushButton *pushButton_Annuler2;
    QWidget *tab_2;
    QTableView *tableView;
    QLabel *label;
    QLineEdit *lineEdit_Rech;
    QLabel *label_4;
    QLabel *label_9;
    QPushButton *pushButton_Recherche;
    QComboBox *comboBox_Trier;
    QLabel *label_10;
    QLabel *label_11;
    QWidget *tab_4;
    QLabel *label_3;
    QLineEdit *lineEdit_Modifier;
    QLabel *label_12;
    QComboBox *comboBox_etat_2;
    QLabel *label_13;
    QComboBox *comboBox_type_2;
    QLabel *label_14;
    QLineEdit *lineEdit_T_2;
    QPushButton *pushButton_Modifier;
    QPushButton *pushButton_SaveModifier;
    QPushButton *pushButton_Annuler_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(829, 604);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 821, 541));
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));
        tab = new QWidget();
        tab->setObjectName("tab");
        lineEdit_ID = new QLineEdit(tab);
        lineEdit_ID->setObjectName("lineEdit_ID");
        lineEdit_ID->setGeometry(QRect(210, 100, 161, 22));
        lineEdit_ID->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_T = new QLineEdit(tab);
        lineEdit_T->setObjectName("lineEdit_T");
        lineEdit_T->setGeometry(QRect(620, 170, 161, 22));
        lineEdit_T->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_5 = new QLabel(tab);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 100, 141, 20));
        label_5->setStyleSheet(QString::fromUtf8(""));
        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(50, 180, 141, 20));
        label_6->setStyleSheet(QString::fromUtf8(""));
        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(450, 100, 141, 20));
        label_7->setStyleSheet(QString::fromUtf8(""));
        label_8 = new QLabel(tab);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(460, 180, 141, 20));
        label_8->setStyleSheet(QString::fromUtf8(""));
        pushButton_Ajouter = new QPushButton(tab);
        pushButton_Ajouter->setObjectName("pushButton_Ajouter");
        pushButton_Ajouter->setGeometry(QRect(270, 320, 101, 41));
        pushButton_Ajouter->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        comboBox_etat = new QComboBox(tab);
        comboBox_etat->addItem(QString());
        comboBox_etat->addItem(QString());
        comboBox_etat->setObjectName("comboBox_etat");
        comboBox_etat->setGeometry(QRect(210, 170, 161, 31));
        comboBox_type = new QComboBox(tab);
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->setObjectName("comboBox_type");
        comboBox_type->setGeometry(QRect(620, 90, 161, 31));
        pushButton_Annuler = new QPushButton(tab);
        pushButton_Annuler->setObjectName("pushButton_Annuler");
        pushButton_Annuler->setGeometry(QRect(450, 320, 101, 41));
        pushButton_Annuler->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_2 = new QLabel(tab_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 100, 111, 31));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));
        pushButton_Supprimer = new QPushButton(tab_3);
        pushButton_Supprimer->setObjectName("pushButton_Supprimer");
        pushButton_Supprimer->setGeometry(QRect(190, 230, 121, 41));
        pushButton_Supprimer->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_supp = new QLineEdit(tab_3);
        lineEdit_supp->setObjectName("lineEdit_supp");
        lineEdit_supp->setGeometry(QRect(210, 100, 181, 31));
        lineEdit_supp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_Annuler2 = new QPushButton(tab_3);
        pushButton_Annuler2->setObjectName("pushButton_Annuler2");
        pushButton_Annuler2->setGeometry(QRect(370, 230, 131, 41));
        pushButton_Annuler2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tableView = new QTableView(tab_2);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(100, 160, 621, 271));
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
        label = new QLabel(tab_2);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 120, 91, 16));
        lineEdit_Rech = new QLineEdit(tab_2);
        lineEdit_Rech->setObjectName("lineEdit_Rech");
        lineEdit_Rech->setGeometry(QRect(200, 120, 113, 22));
        lineEdit_Rech->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(500, 120, 91, 21));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(270, 50, 191, 31));
        label_9->setStyleSheet(QString::fromUtf8("background-color: #dfaea1"));
        pushButton_Recherche = new QPushButton(tab_2);
        pushButton_Recherche->setObjectName("pushButton_Recherche");
        pushButton_Recherche->setGeometry(QRect(330, 120, 91, 24));
        comboBox_Trier = new QComboBox(tab_2);
        comboBox_Trier->addItem(QString());
        comboBox_Trier->addItem(QString());
        comboBox_Trier->addItem(QString());
        comboBox_Trier->setObjectName("comboBox_Trier");
        comboBox_Trier->setGeometry(QRect(600, 120, 121, 21));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(90, 450, 141, 41));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(210, 450, 31, 31));
        label_11->setPixmap(QPixmap(QString::fromUtf8("../../Pictures/pdf.png")));
        label_11->setScaledContents(true);
        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        label_3 = new QLabel(tab_4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 100, 111, 31));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));
        lineEdit_Modifier = new QLineEdit(tab_4);
        lineEdit_Modifier->setObjectName("lineEdit_Modifier");
        lineEdit_Modifier->setGeometry(QRect(170, 100, 181, 31));
        lineEdit_Modifier->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_12 = new QLabel(tab_4);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(50, 200, 141, 20));
        label_12->setStyleSheet(QString::fromUtf8(""));
        comboBox_etat_2 = new QComboBox(tab_4);
        comboBox_etat_2->addItem(QString());
        comboBox_etat_2->addItem(QString());
        comboBox_etat_2->setObjectName("comboBox_etat_2");
        comboBox_etat_2->setGeometry(QRect(170, 190, 181, 31));
        label_13 = new QLabel(tab_4);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(420, 100, 141, 20));
        label_13->setStyleSheet(QString::fromUtf8(""));
        comboBox_type_2 = new QComboBox(tab_4);
        comboBox_type_2->addItem(QString());
        comboBox_type_2->addItem(QString());
        comboBox_type_2->addItem(QString());
        comboBox_type_2->addItem(QString());
        comboBox_type_2->setObjectName("comboBox_type_2");
        comboBox_type_2->setGeometry(QRect(570, 100, 181, 31));
        label_14 = new QLabel(tab_4);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(430, 190, 141, 20));
        label_14->setStyleSheet(QString::fromUtf8(""));
        lineEdit_T_2 = new QLineEdit(tab_4);
        lineEdit_T_2->setObjectName("lineEdit_T_2");
        lineEdit_T_2->setGeometry(QRect(580, 190, 171, 31));
        lineEdit_T_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_Modifier = new QPushButton(tab_4);
        pushButton_Modifier->setObjectName("pushButton_Modifier");
        pushButton_Modifier->setGeometry(QRect(220, 330, 121, 41));
        pushButton_Modifier->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_SaveModifier = new QPushButton(tab_4);
        pushButton_SaveModifier->setObjectName("pushButton_SaveModifier");
        pushButton_SaveModifier->setGeometry(QRect(410, 330, 121, 41));
        pushButton_SaveModifier->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_Annuler_3 = new QPushButton(tab_4);
        pushButton_Annuler_3->setObjectName("pushButton_Annuler_3");
        pushButton_Annuler_3->setGeometry(QRect(590, 330, 101, 41));
        pushButton_Annuler_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 829, 22));
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
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">ID_CHAMBRE</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">ETAT_CHAMBRE</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Type de chambre</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">tarif par nuit</span></p></body></html>", nullptr));
        pushButton_Ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        comboBox_etat->setItemText(0, QCoreApplication::translate("MainWindow", "Occup\303\251e", nullptr));
        comboBox_etat->setItemText(1, QCoreApplication::translate("MainWindow", "Disponible", nullptr));

        comboBox_type->setItemText(0, QCoreApplication::translate("MainWindow", "simple", nullptr));
        comboBox_type->setItemText(1, QCoreApplication::translate("MainWindow", "double", nullptr));
        comboBox_type->setItemText(2, QCoreApplication::translate("MainWindow", "suite", nullptr));
        comboBox_type->setItemText(3, QCoreApplication::translate("MainWindow", "famile", nullptr));

        pushButton_Annuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">ID_CHAMBRE</span></p></body></html>", nullptr));
        pushButton_Supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_Annuler2->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">ID_CHAMBRE :</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Trier par :</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Liste Des Chambres</span></p></body></html>\n"
"\n"
"", nullptr));
        pushButton_Recherche->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        comboBox_Trier->setItemText(0, QCoreApplication::translate("MainWindow", "etat", nullptr));
        comboBox_Trier->setItemText(1, QCoreApplication::translate("MainWindow", "type", nullptr));
        comboBox_Trier->setItemText(2, QCoreApplication::translate("MainWindow", "tarif", nullptr));

        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Exporter en PDF</span></p></body></html>", nullptr));
        label_11->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">ID_CHAMBRE</span></p></body></html>", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">ETAT_CHAMBRE</span></p></body></html>", nullptr));
        comboBox_etat_2->setItemText(0, QCoreApplication::translate("MainWindow", "Occup\303\251e", nullptr));
        comboBox_etat_2->setItemText(1, QCoreApplication::translate("MainWindow", "Disponible", nullptr));

        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Type de chambre</span></p></body></html>", nullptr));
        comboBox_type_2->setItemText(0, QCoreApplication::translate("MainWindow", "simple", nullptr));
        comboBox_type_2->setItemText(1, QCoreApplication::translate("MainWindow", "double", nullptr));
        comboBox_type_2->setItemText(2, QCoreApplication::translate("MainWindow", "suite", nullptr));
        comboBox_type_2->setItemText(3, QCoreApplication::translate("MainWindow", "famile", nullptr));

        label_14->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">tarif par nuit</span></p></body></html>", nullptr));
        pushButton_Modifier->setText(QCoreApplication::translate("MainWindow", "Modifier ", nullptr));
        pushButton_SaveModifier->setText(QCoreApplication::translate("MainWindow", "SaveModifier ", nullptr));
        pushButton_Annuler_3->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Modifier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
