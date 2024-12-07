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
    QTabWidget *label_type_2;
    QWidget *tab_2;
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
    QLabel *label_message;
    QWidget *tab_5;
    QTabWidget *statistique;
    QWidget *tab_7;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineEdit_ID1;
    QLineEdit *lineEdit_ClientID;
    QLineEdit *lineEdit_NbPersonnes;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *lineEdit_Montant;
    QComboBox *comboBox_type_reservation;
    QComboBox *comboBox_statut;
    QComboBox *comboBox_mode_paiement;
    QPushButton *pushButton_Ajouter1;
    QLabel *label_14;
    QDateEdit *dateEdit_Debut;
    QDateEdit *dateEdit_Fin;
    QPushButton *pushButton_Annuler1;
    QLineEdit *lineEdit_Numt;
    QLabel *label_15;
    QTableView *tableView_2;
    QPushButton *pushButton_Recherche1;
    QLabel *label_21;
    QComboBox *pushButton_tri1;
    QPushButton *pushButton_tri1_2;
    QPushButton *pushButton_Supprimer1;
    QPushButton *exporter;
    QComboBox *comboBox_trier_3;
    QLineEdit *lineEdit_Rech2;
    QWidget *tab_8;
    QWidget *label_type2;
    QWidget *tab_3;
    QWidget *tab_6;
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
        label_type_2 = new QTabWidget(centralWidget);
        label_type_2->setObjectName("label_type_2");
        label_type_2->setGeometry(QRect(0, -10, 1401, 721));
        label_type_2->setStyleSheet(QString::fromUtf8("QTabBar::tab {\n"
"    background-color: #4682B4; /* Bleu fonc\303\251 */\n"
"    border: 1px solid #5A9BD3; /* Bordure l\303\251g\303\250rement plus claire */\n"
"    padding: 10px 20px;        /* Agrandir les boutons */\n"
"    font-size: 14px;           /* Taille du texte */\n"
"    font-weight: bold;         /* Texte en gras */\n"
"    margin: 5px;               /* Espacement entre les onglets */\n"
"    border-radius: 5px;        /* Coins arrondis */\n"
"    color: white;              /* Texte en blanc */\n"
"}\n"
"\n"
"/* Style pour l'onglet actif */\n"
"QTabBar::tab:selected {\n"
"    background-color: #1E4B7A; /* Bleu tr\303\250s fonc\303\251 pour l'onglet actif */\n"
"    border: 2px solid #5A9BD3; /* Bordure plus claire pour l'onglet actif */\n"
"    color: white;              /* Texte en blanc */\n"
"}\n"
"\n"
"/* Survol des onglets */\n"
"QTabBar::tab:hover {\n"
"    background-color: #5A9BD3; /* Bleu l\303\251g\303\250rement plus clair au survol */\n"
"    border: 1px solid #4682B4; /* Bordure cor"
                        "respondant \303\240 la couleur de base */\n"
"}"));
        label_type_2->setTabPosition(QTabWidget::TabPosition::West);
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget = new QTabWidget(tab_2);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1301, 631));
        tabWidget->setMaximumSize(QSize(1920, 1680));
        QFont font;
        font.setPointSize(12);
        tabWidget->setFont(font);
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tab = new QWidget();
        tab->setObjectName("tab");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 291, 541));
        groupBox->setSizeIncrement(QSize(5, 0));
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));
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
        pushButton_Ajouter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        pushButton_Annuler = new QPushButton(groupBox);
        pushButton_Annuler->setObjectName("pushButton_Annuler");
        pushButton_Annuler->setGeometry(QRect(150, 420, 111, 41));
        pushButton_Annuler->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
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
        pushButton_Recherche->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        pushButton_Supprimer = new QPushButton(tab);
        pushButton_Supprimer->setObjectName("pushButton_Supprimer");
        pushButton_Supprimer->setGeometry(QRect(830, 80, 101, 31));
        pushButton_Supprimer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        label_17 = new QLabel(tab);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(380, 150, 121, 21));
        comboBox_trier = new QComboBox(tab);
        comboBox_trier->setObjectName("comboBox_trier");
        comboBox_trier->setGeometry(QRect(520, 140, 181, 31));
        pushButton_tri = new QPushButton(tab);
        pushButton_tri->setObjectName("pushButton_tri");
        pushButton_tri->setGeometry(QRect(730, 140, 71, 31));
        pushButton_tri->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        qrcode_button = new QPushButton(tab);
        qrcode_button->setObjectName("qrcode_button");
        qrcode_button->setGeometry(QRect(950, 140, 93, 28));
        qrcode_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        qr_code = new QLabel(tab);
        qr_code->setObjectName("qr_code");
        qr_code->setGeometry(QRect(900, 180, 361, 381));
        qr_code->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));
        pushButton_SMS = new QPushButton(tab);
        pushButton_SMS->setObjectName("pushButton_SMS");
        pushButton_SMS->setGeometry(QRect(800, 460, 91, 31));
        pushButton_SMS->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        comboBox_trier_2 = new QComboBox(tab);
        comboBox_trier_2->addItem(QString());
        comboBox_trier_2->addItem(QString());
        comboBox_trier_2->addItem(QString());
        comboBox_trier_2->setObjectName("comboBox_trier_2");
        comboBox_trier_2->setGeometry(QRect(380, 80, 131, 31));
        pushButton_exporter_2 = new QPushButton(tab);
        pushButton_exporter_2->setObjectName("pushButton_exporter_2");
        pushButton_exporter_2->setGeometry(QRect(390, 460, 101, 31));
        pushButton_exporter_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
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
        label_type->setGeometry(QRect(30, 40, 691, 441));
        label_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_message = new QLabel(tab_4);
        label_message->setObjectName("label_message");
        label_message->setGeometry(QRect(750, 190, 321, 71));
        label_message->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab_4, QString());
        label_type_2->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        statistique = new QTabWidget(tab_5);
        statistique->setObjectName("statistique");
        statistique->setGeometry(QRect(-10, 0, 1321, 721));
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        groupBox_2 = new QGroupBox(tab_7);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(0, -10, 451, 691));
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);\n"
""));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 141, 20));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 100, 161, 20));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 130, 151, 20));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 160, 101, 20));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 190, 151, 20));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 220, 63, 20));
        lineEdit_ID1 = new QLineEdit(groupBox_2);
        lineEdit_ID1->setObjectName("lineEdit_ID1");
        lineEdit_ID1->setGeometry(QRect(190, 30, 113, 26));
        lineEdit_ID1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_ClientID = new QLineEdit(groupBox_2);
        lineEdit_ClientID->setObjectName("lineEdit_ClientID");
        lineEdit_ClientID->setGeometry(QRect(190, 60, 113, 26));
        lineEdit_ClientID->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_NbPersonnes = new QLineEdit(groupBox_2);
        lineEdit_NbPersonnes->setObjectName("lineEdit_NbPersonnes");
        lineEdit_NbPersonnes->setGeometry(QRect(190, 190, 113, 26));
        lineEdit_NbPersonnes->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 260, 121, 20));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 300, 171, 20));
        lineEdit_Montant = new QLineEdit(groupBox_2);
        lineEdit_Montant->setObjectName("lineEdit_Montant");
        lineEdit_Montant->setGeometry(QRect(190, 260, 113, 26));
        lineEdit_Montant->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        comboBox_type_reservation = new QComboBox(groupBox_2);
        comboBox_type_reservation->addItem(QString());
        comboBox_type_reservation->addItem(QString());
        comboBox_type_reservation->addItem(QString());
        comboBox_type_reservation->setObjectName("comboBox_type_reservation");
        comboBox_type_reservation->setGeometry(QRect(190, 100, 111, 26));
        comboBox_statut = new QComboBox(groupBox_2);
        comboBox_statut->addItem(QString());
        comboBox_statut->addItem(QString());
        comboBox_statut->addItem(QString());
        comboBox_statut->setObjectName("comboBox_statut");
        comboBox_statut->setGeometry(QRect(190, 220, 111, 26));
        comboBox_statut->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        comboBox_mode_paiement = new QComboBox(groupBox_2);
        comboBox_mode_paiement->addItem(QString());
        comboBox_mode_paiement->addItem(QString());
        comboBox_mode_paiement->addItem(QString());
        comboBox_mode_paiement->setObjectName("comboBox_mode_paiement");
        comboBox_mode_paiement->setGeometry(QRect(190, 300, 111, 26));
        pushButton_Ajouter1 = new QPushButton(groupBox_2);
        pushButton_Ajouter1->setObjectName("pushButton_Ajouter1");
        pushButton_Ajouter1->setGeometry(QRect(50, 410, 93, 29));
        pushButton_Ajouter1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 30, 151, 20));
        dateEdit_Debut = new QDateEdit(groupBox_2);
        dateEdit_Debut->setObjectName("dateEdit_Debut");
        dateEdit_Debut->setGeometry(QRect(190, 130, 110, 26));
        dateEdit_Fin = new QDateEdit(groupBox_2);
        dateEdit_Fin->setObjectName("dateEdit_Fin");
        dateEdit_Fin->setGeometry(QRect(190, 160, 110, 26));
        pushButton_Annuler1 = new QPushButton(groupBox_2);
        pushButton_Annuler1->setObjectName("pushButton_Annuler1");
        pushButton_Annuler1->setGeometry(QRect(240, 410, 93, 29));
        pushButton_Annuler1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        lineEdit_Numt = new QLineEdit(groupBox_2);
        lineEdit_Numt->setObjectName("lineEdit_Numt");
        lineEdit_Numt->setGeometry(QRect(190, 350, 113, 22));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(20, 350, 71, 16));
        tableView_2 = new QTableView(tab_7);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setGeometry(QRect(590, 160, 521, 401));
        tableView_2->setStyleSheet(QString::fromUtf8("QTableView {\n"
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
        pushButton_Recherche1 = new QPushButton(tab_7);
        pushButton_Recherche1->setObjectName("pushButton_Recherche1");
        pushButton_Recherche1->setGeometry(QRect(920, 40, 93, 29));
        pushButton_Recherche1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #B4A9D5; /* Couleur plus douce pour l'\303\251tat normal */\n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}\n"
""));
        label_21 = new QLabel(tab_7);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(580, 120, 71, 21));
        label_21->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));
        pushButton_tri1 = new QComboBox(tab_7);
        pushButton_tri1->addItem(QString());
        pushButton_tri1->addItem(QString());
        pushButton_tri1->addItem(QString());
        pushButton_tri1->setObjectName("pushButton_tri1");
        pushButton_tri1->setGeometry(QRect(770, 120, 121, 26));
        pushButton_tri1_2 = new QPushButton(tab_7);
        pushButton_tri1_2->setObjectName("pushButton_tri1_2");
        pushButton_tri1_2->setGeometry(QRect(960, 120, 93, 29));
        pushButton_tri1_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        pushButton_Supprimer1 = new QPushButton(tab_7);
        pushButton_Supprimer1->setObjectName("pushButton_Supprimer1");
        pushButton_Supprimer1->setGeometry(QRect(1030, 40, 93, 29));
        pushButton_Supprimer1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        exporter = new QPushButton(tab_7);
        exporter->setObjectName("exporter");
        exporter->setGeometry(QRect(1000, 570, 111, 29));
        exporter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16px; \n"
"    color: #00207F;\n"
"    background-color: #DEDFF5; \n"
"    border: 2px solid blue;\n"
"    border-radius: 10px; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #7C73BB; /* Couleur au clic */\n"
"}"));
        comboBox_trier_3 = new QComboBox(tab_7);
        comboBox_trier_3->addItem(QString());
        comboBox_trier_3->addItem(QString());
        comboBox_trier_3->addItem(QString());
        comboBox_trier_3->setObjectName("comboBox_trier_3");
        comboBox_trier_3->setGeometry(QRect(570, 40, 131, 26));
        lineEdit_Rech2 = new QLineEdit(tab_7);
        lineEdit_Rech2->setObjectName("lineEdit_Rech2");
        lineEdit_Rech2->setGeometry(QRect(770, 40, 113, 26));
        statistique->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        label_type2 = new QWidget(tab_8);
        label_type2->setObjectName("label_type2");
        label_type2->setGeometry(QRect(260, 40, 411, 281));
        statistique->addTab(tab_8, QString());
        label_type_2->addTab(tab_5, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_type_2->addTab(tab_3, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        label_type_2->addTab(tab_6, QString());
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

        label_type_2->setCurrentIndex(1);
        tabWidget->setCurrentIndex(1);
        statistique->setCurrentIndex(0);


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
        comboBox_trier_2->setItemText(1, QCoreApplication::translate("MainWindow", "etat", nullptr));
        comboBox_trier_2->setItemText(2, QCoreApplication::translate("MainWindow", "tarif", nullptr));

        pushButton_exporter_2->setText(QCoreApplication::translate("MainWindow", "Exporter pdf", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">id_reservation :</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Aceuille", nullptr));
        label_type->setText(QString());
        label_message->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Fonctionnaliter", nullptr));
        label_type_2->setTabText(label_type_2->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Chambre", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Ajouter r\303\251servation", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Id du client ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "type de la r\303\251servation ", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Date de d\303\251but", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Date de fin", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Nombre de personnes", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Montant total", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Mode de paiment", nullptr));
        comboBox_type_reservation->setItemText(0, QCoreApplication::translate("MainWindow", "Chambre", nullptr));
        comboBox_type_reservation->setItemText(1, QCoreApplication::translate("MainWindow", "Restaurant", nullptr));
        comboBox_type_reservation->setItemText(2, QCoreApplication::translate("MainWindow", "Parking", nullptr));

        comboBox_statut->setItemText(0, QCoreApplication::translate("MainWindow", "confirm\303\251e", nullptr));
        comboBox_statut->setItemText(1, QCoreApplication::translate("MainWindow", " en attente", nullptr));
        comboBox_statut->setItemText(2, QCoreApplication::translate("MainWindow", "annul\303\251e", nullptr));

        comboBox_mode_paiement->setItemText(0, QCoreApplication::translate("MainWindow", "carte bancaire", nullptr));
        comboBox_mode_paiement->setItemText(1, QCoreApplication::translate("MainWindow", "esp\303\251ces", nullptr));
        comboBox_mode_paiement->setItemText(2, QCoreApplication::translate("MainWindow", "Virement", nullptr));

        pushButton_Ajouter1->setText(QCoreApplication::translate("MainWindow", "enregistrer", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Id de la r\303\251servation", nullptr));
        pushButton_Annuler1->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "num tel", nullptr));
        pushButton_Recherche1->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Trier par:", nullptr));
        pushButton_tri1->setItemText(0, QCoreApplication::translate("MainWindow", "Montant", nullptr));
        pushButton_tri1->setItemText(1, QCoreApplication::translate("MainWindow", "statut", nullptr));
        pushButton_tri1->setItemText(2, QCoreApplication::translate("MainWindow", "date_debut", nullptr));

        pushButton_tri1_2->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        pushButton_Supprimer1->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        exporter->setText(QCoreApplication::translate("MainWindow", "exporter", nullptr));
        comboBox_trier_3->setItemText(0, QCoreApplication::translate("MainWindow", "id_reservation", nullptr));
        comboBox_trier_3->setItemText(1, QCoreApplication::translate("MainWindow", "id_client", nullptr));
        comboBox_trier_3->setItemText(2, QCoreApplication::translate("MainWindow", "montant", nullptr));

        statistique->setTabText(statistique->indexOf(tab_7), QCoreApplication::translate("MainWindow", "Aceuille", nullptr));
        statistique->setTabText(statistique->indexOf(tab_8), QCoreApplication::translate("MainWindow", "Fonctionnalite", nullptr));
        label_type_2->setTabText(label_type_2->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Reservation", nullptr));
        label_type_2->setTabText(label_type_2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Logistique", nullptr));
        label_type_2->setTabText(label_type_2->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Service", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
