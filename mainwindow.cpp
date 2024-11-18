#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <QString>
#include "financier.h"
#include <QDateEdit>
#include <QDate>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QDesktopServices>
#include<QtMultimedia>
#include <QMediaPlayer>
#include <QUrl>


#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
     ui->tableView_6->setModel(ETMP.afficher());

    M_PLAYER=new QMediaPlayer();

     ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
     ui->pause_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));



     connect(M_PLAYER, &QMediaPlayer::positionChanged, ui->horizontalSlider, &QSlider::setValue);
     connect(M_PLAYER, &QMediaPlayer::durationChanged, ui->horizontalSlider, &QSlider::setMaximum);

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
void MainWindow::clearFields() {
    ui->lineEdit_Desc->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_Montant->clear();
    ui->comboBox_type->setCurrentIndex(0);
    ui->comboBox_mode->setCurrentIndex(0);

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
    int id;
    QDate dateTransaction = ui->dateEdit->date();
    QString montant = ui->lineEdit_Montant->text();
    QString desc = ui->lineEdit_Desc->text();
    QString type = ui->comboBox_type->currentText();
    QString modePaiement = ui->comboBox_mode->currentText();

    // Ne pas passer l'ID car il est généré automatiquement
    financier f(id,dateTransaction, montant, desc, type, modePaiement);
    bool test = f.Add();  // L'ID sera géré par la base de données

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout Effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non Effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    ui->tableView_6->setModel(f.afficher());
    clearFields();  // Effacer les champs après l'ajout
}










void MainWindow::on_tableView_6_activated(const QModelIndex &index)
{
    QSqlQuery query;
    QString idTransaction = ui->tableView_6->model()->data(index).toString(); // On utilise ID_TRANSACTION pour l'identification

    // Rechercher l'enregistrement uniquement par ID_TRANSACTION (car c'est une clé unique)
    query.prepare("SELECT * FROM TRANSACTIONS WHERE ID_TRANSACTION = :id");
    query.bindValue(":id", idTransaction);

    if (query.exec() && query.next())
    {
        ui->lineEdit_modifID->setText(query.value("ID_TRANSACTION").toString());
        ui->lineEdit_modifMONTANT->setText(query.value("MONTANT").toString());
        ui->lineEdit_modifDESC->setText(query.value("DESCRIPTION").toString());
        ui->comboBox_mode_2->setCurrentText(query.value("MODE_PAIEMENT").toString());
        ui->comboBox_type_2->setCurrentText(query.value("TYPE").toString());

        // Gestion de la date de transaction
        QString dateStr = query.value("DATE_TRANSACTION").toString();
        QDate dateTransaction = QDate::fromString(dateStr, "yyyy-MM-dd");

        if (dateTransaction.isValid()) {
            ui->dateEdit_2->setDate(dateTransaction);
        } else {
            qDebug() << "Erreur : Format de date incorrect pour DATE_TRANSACTION";
        }
    }
}


void MainWindow::on_modifier_button_clicked()
{

    QDate dateTransaction =ui-> dateEdit_2->date();
    QString montant = ui->lineEdit_modifMONTANT->text();
    int id = ui->lineEdit_modifID->text().toInt();
    QString desc = ui->lineEdit_modifDESC->text();
    QString type =ui->comboBox_type_2->currentText();
    QString modePaiement =ui->comboBox_mode_2->currentText();
    financier f( id,dateTransaction,  montant ,  desc ,  type ,  modePaiement );
    bool test=f.modifier_paiement();

    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("modify effectué\n""click cancel to exit."),QMessageBox::Cancel);
        ui->tableView_6->setModel(f.afficher());
        if (id > 0) ui->lineEdit_modifID->clear();
        if (!montant.isEmpty()) ui->lineEdit_modifMONTANT->clear();
        if (!desc.isEmpty()) ui->lineEdit_modifDESC->clear();
        if (!type.isEmpty()) ui->comboBox_type_2->setCurrentText("");
        if (!modePaiement.isEmpty()) ui->comboBox_mode_2->setCurrentText("");
         if (dateTransaction.isValid()) ui->dateEdit_2->clear();

    }
}


void MainWindow::on_tri_clicked()
{
    ui->tableView_6->setModel(ETMP.tri_paiement());
}






void MainWindow::on_PDF_clicked()
{

        QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
        if (!fileName.isEmpty()) {
            financier f;
            QSqlQueryModel* model = f.afficher();
            // Ajoutez des instructions de débogage pour afficher le contenu du modèle
            qDebug() << "Nombre de lignes dans le modèle :" << model->rowCount();
            qDebug() << "Nombre de colonnes dans le modèle :" << model->columnCount();
            for (int row = 0; row < model->rowCount(); ++row) {
                QString rowData;
                for (int column = 0; column < model->columnCount(); ++column) {
                    QModelIndex index = model->index(row, column);
                    rowData += model->data(index).toString() + "\t";
                }
                qDebug() << "Ligne " << row << ":" << rowData;
            }
            if (f.PDF(fileName, model)) {
                QMessageBox::information(this, "Exportation PDF", "Les données ont été exportées en PDF avec succès !");
            } else {
                QMessageBox::warning(this, "Exportation PDF", "Échec de l'exportation en PDF.");
            }
        }

    }








    void MainWindow::on_pushButton_3_clicked()
    {financier f;
        int id = ui->lineEdit_montant_search->text().toInt();
        QSqlQueryModel* searchResultModel = nullptr;
        bool test = f.recherche(id, searchResultModel);

        if (test) {
            if (searchResultModel && searchResultModel->rowCount() > 0) {
                ui->tableView_7->setModel(searchResultModel);
            } else {
                QMessageBox::information(this, "Information", "Aucun transaction"
                                                              " trouvé avec ce id.");
                ui->tableView_7->setModel(nullptr);
            }
        } else {

            QMessageBox::critical(this, "Information", "La recherche du transaction a échoué.");
        }
        clearFields();
    }









    void MainWindow::on_statistique_clicked()
    {

        QSqlQueryModel *model = f.afficher();
        f.stat_paiement(model, ui->chartView);

    }


    void MainWindow::on_pushButton_delete_clicked()
    {
        int id = ui->lineEdit_IDSUPP->text().toInt();
        bool test = ETMP.supprimer(id); // Suppression de la transaction

        if (test) {

            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée et ."), QMessageBox::Cancel);


            // Actualiser la vue
            ui->tableView_6->setModel(ETMP.afficher());
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Suppression non effectuée."), QMessageBox::Cancel);
        }

        clearFields();
    }

    void MainWindow::on_play_button_clicked()
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Sélectionnez un fichier audio"), "", tr("Fichiers MP3 (*.mp3)"));

        if (!fileName.isEmpty()) {
            // Définir la source média
            M_PLAYER->setSource(QUrl::fromLocalFile(fileName));

            // Configurez une sortie audio
            QAudioOutput *audioOutput = new QAudioOutput(this);
            M_PLAYER->setAudioOutput(audioOutput);
            audioOutput->setVolume(0.5); // Réglez le volume à 50%

            // Lecture immédiate
            M_PLAYER->play();
        }
    }

    void MainWindow::on_pause_button_clicked()
    {
        if (M_PLAYER->playbackState() == QMediaPlayer::PlayingState) {
            M_PLAYER->pause();
        } else if (M_PLAYER->playbackState() == QMediaPlayer::PausedState) {
            M_PLAYER->play();
        }
    }

    void MainWindow::on_horizontalSlider_valueChanged(int value)
    {
        M_PLAYER->setPosition(value);
    }
