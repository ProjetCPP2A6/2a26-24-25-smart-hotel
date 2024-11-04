#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <QString>
#include "financier.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
     ui->tableView_6->setModel(ETMP.afficher());


    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);

    stackedWidget = ui->stackedWidget;

    buttons[0] = ui->pushButton_2;
    buttons[1] = ui->pushButton_7;
    buttons[2] = ui->pushButton_16;
    buttons[3] = ui->pushButton_15;
    buttons[4] = ui->pushButton_18;
    buttons[5] = ui->pushButton_19;
    buttons[6] = ui->pushButton_1;
    buttons[7] = ui->pushButton_29;
    buttons[8] = ui->pushButton_28;
    buttons[9] = ui->pushButton_27;
    buttons[10] = ui->pushButton_30;
    buttons[11] = ui->pushButton_31;
    buttons[12] = ui->pushButton_4;
    buttons[13] = ui->pushButton_41;
    buttons[14] = ui->pushButton_40;
    buttons[15] = ui->pushButton_39;
    buttons[16] = ui->pushButton_42;
    buttons[17] = ui->pushButton_43;
    buttons[18] = ui->pushButton_5;
    buttons[19] = ui->pushButton_48;
    buttons[20] = ui->pushButton_47;
    buttons[21] = ui->pushButton_46;
    buttons[22] = ui->pushButton_49;
    buttons[23] = ui->pushButton_50;
    buttons[24] = ui->pushButton_6;
    buttons[25] = ui->pushButton_60;
    buttons[26] = ui->pushButton_59;
    buttons[27] = ui->pushButton_58;
    buttons[28] = ui->pushButton_64;
    buttons[29] = ui->pushButton_62;


    connect(buttons[0], &QPushButton::clicked, this, &MainWindow::showPage1);
    connect(buttons[1], &QPushButton::clicked, this, &MainWindow::showPage1);
    connect(buttons[2], &QPushButton::clicked, this, &MainWindow::showPage1);
    connect(buttons[3], &QPushButton::clicked, this, &MainWindow::showPage1);
    connect(buttons[4], &QPushButton::clicked, this, &MainWindow::showPage1);
    connect(buttons[5], &QPushButton::clicked, this, &MainWindow::showPage1);

    connect(buttons[6], &QPushButton::clicked, this, &MainWindow::showPage2);
    connect(buttons[7], &QPushButton::clicked, this, &MainWindow::showPage2);
    connect(buttons[8], &QPushButton::clicked, this, &MainWindow::showPage2);
    connect(buttons[9], &QPushButton::clicked, this, &MainWindow::showPage2);
    connect(buttons[10], &QPushButton::clicked, this, &MainWindow::showPage2);
    connect(buttons[11], &QPushButton::clicked, this, &MainWindow::showPage2);

    connect(buttons[12], &QPushButton::clicked, this, &MainWindow::showPage3);
    connect(buttons[13], &QPushButton::clicked, this, &MainWindow::showPage3);
    connect(buttons[14], &QPushButton::clicked, this, &MainWindow::showPage3);
    connect(buttons[15], &QPushButton::clicked, this, &MainWindow::showPage3);
    connect(buttons[16], &QPushButton::clicked, this, &MainWindow::showPage3);
    connect(buttons[17], &QPushButton::clicked, this, &MainWindow::showPage3);

    connect(buttons[18], &QPushButton::clicked, this, &MainWindow::showPage4);
    connect(buttons[19], &QPushButton::clicked, this, &MainWindow::showPage4);
    connect(buttons[20], &QPushButton::clicked, this, &MainWindow::showPage4);
    connect(buttons[21], &QPushButton::clicked, this, &MainWindow::showPage4);
    connect(buttons[22], &QPushButton::clicked, this, &MainWindow::showPage4);
    connect(buttons[23], &QPushButton::clicked, this, &MainWindow::showPage4);

    connect(buttons[24], &QPushButton::clicked, this, &MainWindow::showPage5);
    connect(buttons[25], &QPushButton::clicked, this, &MainWindow::showPage5);
    connect(buttons[26], &QPushButton::clicked, this, &MainWindow::showPage5);
    connect(buttons[27], &QPushButton::clicked, this, &MainWindow::showPage5);
    connect(buttons[28], &QPushButton::clicked, this, &MainWindow::showPage5);
    connect(buttons[29], &QPushButton::clicked, this, &MainWindow::showPage5);
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::validateLogin(const QString &username, const QString &password) {

    const QString correctUsername = "admin";
    const QString correctPassword = "password123";

    return (username == correctUsername && password == correctPassword);
}

void MainWindow::onLoginButtonClicked() {

    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();


    if (validateLogin(username, password)) {

        ui->stackedWidget->setCurrentIndex(1);
    } else {

        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}
void MainWindow::showPage1() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showPage2() {
    stackedWidget->setCurrentIndex(4);
}

void MainWindow::showPage3() {
    stackedWidget->setCurrentIndex(6);
}

void MainWindow::showPage4() {
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::showPage5() {
    stackedWidget->setCurrentIndex(5);
}

void MainWindow::showPage6() {
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::showPage7() {
    stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_addButton_clicked()
{
    QDate dateTransaction = QDate::fromString(ui->lineEdit_Date->text(), "yyyy-MM-dd");
    int montant = ui->lineEdit_Montant->text().toInt();
    int id = ui->lineEdit_ID->text().toInt();
    QString desc = ui->lineEdit_Desc->text();
    QString type =ui->comboBox_type->currentText();
    QString modePaiement =ui->comboBox_mode->currentText();
    financier f( id,dateTransaction,  montant ,  desc ,  type ,  modePaiement );
    bool test=f.Add();
    if(test){
        ui->tableView_6->setModel(ETMP.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectue"),QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("faux"),QObject::tr("ajout non effectue"),QMessageBox::Cancel);
    }
}



void MainWindow::on_delete_button_clicked()
{
    int id=ui->lineEdit_IDSUPP->text().toInt();
    bool test=ETMP.supprimer(id);
    if(test){
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("supp effectue"),QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("faux"),QObject::tr("supp non effectue"),QMessageBox::Cancel);
    }
}


void MainWindow::on_modifier_button_clicked()
{
    QDate dateTransaction = QDate::fromString(ui->lineEdit_modifDATE->text(), "yyyy-MM-dd");
    int montant = ui->lineEdit_modifMONTANT->text().toInt();
    int id = ui->lineEdit_modifID->text().toInt();
    QString desc = ui->lineEdit_modifDESC->text();
    QString type =ui->comboBox_modifTYPE->currentText();
    QString modePaiement =ui->comboBox_modifMODE->currentText();

   financier f( id,dateTransaction,  montant ,  desc ,  type ,  modePaiement );
    bool test =f.Modifier_Employe( id,dateTransaction,  montant,  desc,  type,  modePaiement);
   if(test)
    {ui->tableView_6->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr(" modifiée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else{
        QMessageBox::critical(nullptr, QObject::tr("non Modif "),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

}

