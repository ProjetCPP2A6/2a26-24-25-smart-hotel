#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Chambre.h"
#include<QString>
#include <QMessageBox>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>
#include<QSqlError>
#include <utility>


#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QTableView>
#include <QFileDialog>
#include <QTextDocument>
#include <QDebug>


#include <QtSql/QSqlQueryModel>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QMediaPlayer>
#include <QPen>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlQueryModel>
#include <QPieSeries>
#include <QChart>
#include <QChartView>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlQueryModel>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>



#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>

#include "qrcode.h"

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDate>


//***************** declaration gs_reservation *************************

#include <QSqlError>
#include <QDebug>
#include "reservation.h"
#include <QFileDialog>

#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
//#include "notificationwidget.h"
#include <QSystemTrayIcon>
#include <QTimer>

#include "connection.h"
#include <QMessageBox>
#include <QSqlDatabase>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_2->setModel(Rtmp.afficher());

    // Création de la connexion à la base de données
    Connection connection;
    if (!connection.createconnection()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données.");
        return;  // Arrête l'exécution si la connexion échoue
    }

    // Si la connexion réussit, vous pouvez afficher les données ou effectuer d'autres actions
    ui->tableView_2->setModel(Rtmp.afficher());
    rafraichirTable();



    ui->lineEdit_ID->setValidator(new QIntValidator(0,9999,this));
    connect(ui->lineEdit_ID, &QLineEdit::editingFinished, this, &MainWindow::on_lineEdit_ID_editingFinished);
    connect(ui->pushButton_tri, &QPushButton::clicked, this, &MainWindow::on_pushButton_tri_clicked);
    //connect(A.getserial(), &QSerialPort::readyRead, this, &MainWindow::readDataFromArduino);



    ui->comboBox_trier->addItem("etat");
    ui->comboBox_trier->addItem("type");
    ui->comboBox_trier->addItem("tarif");
    ui->tableView->setModel(CHtmp.afficher());

    //**********************gs reservation ****************************************

    // Connexion des boutons à leurs slots
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimer_clicked);
    connect(ui->trier, &QPushButton::clicked, this, &MainWindow::on_trier_clicked);
    connect(ui->rechercher, &QPushButton::clicked, this, &MainWindow::on_rechercher_clicked);
    connect(ui->exporter, &QPushButton::clicked, this, &MainWindow::on_exporter_clicked); // Connexion du bouton d'exportation en PDF
    connect(ui->pushButton_statistiques, &QPushButton::clicked, this, &MainWindow::on_pushButton_statistiques_clicked);
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifier_clicked); // Connexion du bouton d'exportation en PDF

    connect(ui->ajouter, &QPushButton::clicked, this, &MainWindow::on_ajouter_clicked); // Connexion du bouton d'exportation en PDF
    connect(ui->enregistrer, &QPushButton::clicked, this, &MainWindow::on_enregistrer_clicked); // Connexion du bouton d'exportation en PDF
}

MainWindow::~MainWindow()
{


    connection.closeconnection();

    delete ui;

}


/*void MainWindow::update_label()
{
    // Exemple de mise à jour d'un label dans l'interface utilisateur
    ui->label->setText("Mise à jour du label");
}*/

void MainWindow::on_pushButton_Ajouter_clicked()
{

    int idchambre = ui->lineEdit_ID->text().toInt();
    QString etat = ui->comboBox_etat->currentText();
    QString type = ui->comboBox_type->currentText();
    float tarif = ui->lineEdit_T->text().toFloat();

    // Validation des champs
    if (idchambre <= 0 || etat.isEmpty() || type.isEmpty() || tarif <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer des informations valides.");
        return;
    }

    // Vérification de l'existence de l'ID
    QString dummyEtat, dummyType;
    float dummyTarif;
    if (getChambredata(idchambre, dummyEtat, dummyType, dummyTarif)) {
        // Si l'ID est trouvé, on effectue une modification
        QSqlQuery query;
        query.prepare("UPDATE gs_chambre SET etat = :etat, type = :type, tarif = :tarif WHERE idchambre = :idchambre");
        query.bindValue(":idchambre", idchambre);
        query.bindValue(":etat", etat);
        query.bindValue(":type", type);
        query.bindValue(":tarif", tarif);

        if (query.exec()) {
            QMessageBox::information(this, "Modification", "Modification effectuée avec succès.");
            ui->tableView->setModel(CHtmp.afficher());
            // Effacez les champs après la modification
            ui->lineEdit_ID->clear();
            ui->lineEdit_T->clear();
            ui->comboBox_etat->setCurrentIndex(-1);
            ui->comboBox_type->setCurrentIndex(-1);
        } else {
            qDebug() << "Erreur lors de la modification : " << query.lastError().text();
            QMessageBox::critical(this, "Erreur", "Échec de la modification.");
        }
    } else {
        // Si l'ID n'est pas trouvé, on effectue un ajout
        Chambre CH(idchambre, etat, type, tarif);
        if (CH.ajouter()) {
            QMessageBox::information(this, "Ajout", "Ajout effectué avec succès.");
            ui->tableView->setModel(CHtmp.afficher());
            // Effacez les champs après l'ajout
            ui->lineEdit_ID->clear();
            ui->lineEdit_T->clear();
            ui->comboBox_etat->setCurrentIndex(-1);
            ui->comboBox_type->setCurrentIndex(-1);
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout.");
        }
    }

}


void MainWindow::on_comboBox_etat_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->comboBox_etat->setCurrentText("Occupee");
        break;
    case 1:
        ui->comboBox_etat->setCurrentText("Disponible");
        break;
    default :
        break;
    }
}


void MainWindow::on_comboBox_type_activated (int index)
{
    switch (index)
    {
    case 0:
        ui->comboBox_type->setCurrentText("simple");
        break;
    case 1:
        ui->comboBox_type->setCurrentText("double");
        break;
    case 2:
        ui->comboBox_type->setCurrentText("suite");
        break;
    case 3:
        ui->comboBox_type->setCurrentText("famile");
        break;
    default :
        break;
    }
}


void MainWindow::on_pushButton_Supprimer_clicked()
{
    QString critere = ui->comboBox_trier_2->currentText();
    QString valeurRecherchee = ui->lineEdit_Rech->text();

    if (critere == "idchambre") {
        int idchambre = valeurRecherchee.toInt();

        // Vérifiez si l'ID de la chambre existe avant de supprimer
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM gs_chambre WHERE idchambre = :idchambre");
        query.bindValue(":idchambre", idchambre);
        query.exec();

        if (query.next() && query.value(0).toInt() > 0) {
            // L'ID existe, procéder à la suppression
            bool test = CHtmp.supprimer(idchambre);
            if (test) {
                ui->tableView->setModel(CHtmp.afficher());
                QMessageBox::information(this, QObject::tr("Succès"),
                                         QObject::tr("Suppression effectuée avec succès."),
                                         QMessageBox::Ok);
                // Effacer les champs après la suppression
                ui->lineEdit_Rech->clear();
            } else {
                QMessageBox::critical(this, QObject::tr("Échec"),
                                      QObject::tr("La suppression n'a pas pu être effectuée."),
                                      QMessageBox::Ok);
            }
        } else {
            QMessageBox::warning(this, QObject::tr("Erreur"),
                                 QObject::tr("L'ID spécifié n'existe pas."),
                                 QMessageBox::Ok);
        }
    } else {
        QMessageBox::warning(this, QObject::tr("Erreur"),
                             QObject::tr("Veuillez sélectionner 'idchambre' comme critère de recherche."),
                             QMessageBox::Ok);
    }
}


bool MainWindow::getChambredata(const int &idchambre,QString &etat,QString &type,float &tarif)
{

    QSqlQuery query;
    query.prepare("SELECT etat, type, tarif FROM gs_chambre WHERE idchambre = :idchambre");
    query.bindValue(":idchambre", idchambre);

    if (query.exec() && query.next()) {
        etat = query.value("etat").toString();
        type = query.value("type").toString();
        tarif = query.value("tarif").toFloat();
        return true;
    } else {
        return false;
    }
}


bool MainWindow::loadChambreData(int idchambre)
{
    QString etat, type;
    float tarif;

    if (getChambredata(idchambre, etat, type, tarif)) {
        // Vérifier les options de comboBox_etat
        qDebug() << "Options de comboBox_etat avant la sélection :";
        for (int i = 0; i < ui->comboBox_etat->count(); ++i) {
            qDebug() << "Option" << i << ":" << ui->comboBox_etat->itemText(i);
        }

        // Vider et remplir comboBox_etat pour éviter les doublons ou les valeurs manquantes
        ui->comboBox_etat->clear();
        ui->comboBox_etat->addItem("Disponible");
        ui->comboBox_etat->addItem("Occupee");


        // Bloquer les signaux pour éviter les messages de changement
        ui->comboBox_etat->blockSignals(true);
        ui->comboBox_type->blockSignals(true);

        // Trouver l'index correspondant à la valeur de etat dans comboBox_etat
        int indexEtat = ui->comboBox_etat->findText(etat);
        if (indexEtat != -1) {
            // Si la valeur est trouvée, la sélectionner
            ui->comboBox_etat->setCurrentIndex(indexEtat);
        } else {
            // Si la valeur n'est pas trouvée, définir directement le texte
            qDebug() << "La valeur de 'etat' n'est pas trouvée dans comboBox_etat, utilisation de setCurrentText";
            ui->comboBox_etat->setCurrentText(etat);
        }

        // Trouver l'index pour le type et définir la valeur
        int indexType = ui->comboBox_type->findText(type);
        if (indexType != -1) {
            ui->comboBox_type->setCurrentIndex(indexType);
        } else {
            ui->comboBox_type->setCurrentText(type);
        }

        // Définir le tarif
        ui->lineEdit_T->setText(QString::number(tarif, 'f', 2));
        // Débloquer les signaux après la modification
        ui->comboBox_etat->blockSignals(false);
        ui->comboBox_type->blockSignals(false);

        // Forcer la mise à jour de l'interface
        ui->comboBox_etat->update();
        ui->comboBox_type->update();

        return true;
    }
    return false;
}


void MainWindow::on_lineEdit_ID_editingFinished()
{
    int idchambre = ui->lineEdit_ID->text().toInt();
    // Si l'ID est supérieur à zéro, on ne vérifie l'existence de l'ID qu'au clic du bouton Ajouter/Modifier
    if (idchambre > 0) {
        loadChambreData(idchambre);
    }
}


void MainWindow::on_pushButton_Annuler_clicked()
{
    ui->lineEdit_ID->clear();
    ui->comboBox_etat->setCurrentIndex(-1);
    ui->comboBox_type->setCurrentIndex(-1);
    ui->lineEdit_T->clear();
}


void MainWindow::on_pushButton_tri_clicked()
{
    QString triOption = ui->comboBox_trier->currentText(); // Récupère l'option de tri
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Vérifie l'option choisie et effectue le tri
    if (triOption == "etat") {
        query.prepare("SELECT * FROM gs_chambre ORDER BY etat ASC, idchambre ASC");
    } else if (triOption == "type") {
        query.prepare("SELECT * FROM gs_chambre ORDER BY type ASC, idchambre ASC");
    } else if (triOption == "tarif") { // Ajout de l'option de tri par tarif
        query.prepare("SELECT * FROM gs_chambre ORDER BY tarif ASC, idchambre ASC");
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une option de tri valide.");
        return;
    }

    // Exécute la requête et met à jour la tableView
    if (query.exec()) {
        model->setQuery(std::move(query));
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec du tri : " + query.lastError().text());
    }

}


void MainWindow::on_pushButton_Recherche_clicked()
{
    QString critere = ui->comboBox_trier_2->currentText();
    QString valeurRecherchee = ui->lineEdit_Rech->text();

    // Vérifiez si la valeur entrée est vide
    if (valeurRecherchee.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur pour la recherche.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (critere == "idchambre") {
        // Recherche par ID
        query.prepare("SELECT * FROM gs_chambre WHERE idchambre = :valeur");
        query.bindValue(":valeur", valeurRecherchee);
    } else if (critere == "tarif") {
        // Recherche par tarif (avec tolérance)
        bool conversionOk;
        double tarif = valeurRecherchee.toDouble(&conversionOk);

        if (!conversionOk) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer un tarif valide (format : 150.25).");
            return;
        }

        // Utilisation d'une plage pour éviter les problèmes de précision
        double tolerance = 0.01;
        double minTarif = tarif - tolerance;
        double maxTarif = tarif + tolerance;

        query.prepare("SELECT * FROM gs_chambre WHERE tarif BETWEEN :minTarif AND :maxTarif");
        query.bindValue(":minTarif", minTarif);
        query.bindValue(":maxTarif", maxTarif);
    } else if (critere == "etat") {
        // Recherche par état
        if (valeurRecherchee != "Disponible" && valeurRecherchee != "Occupee") {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer un état valide (Disponible ou Occupee).");
            return;
        }

        query.prepare("SELECT * FROM gs_chambre WHERE etat = :valeur");
        query.bindValue(":valeur", valeurRecherchee);
    } else {
        QMessageBox::warning(this, "Erreur", "Critère de recherche inconnu.");
        return;
    }

    // Exécute la requête
    if (query.exec()) {
        model->setQuery(std::move(query));
        ui->tableView->setModel(model);

        // Vérifie si des résultats ont été trouvés
        if (model->rowCount() > 0) {
            // Applique une coloration verte aux lignes trouvées
            for (int row = 0; row < model->rowCount(); ++row) {
                for (int col = 0; col < model->columnCount(); ++col) {
                    ui->tableView->model()->setData(
                        model->index(row, col), QBrush(Qt::green), Qt::BackgroundRole
                        );
                }
            }
        } else {
            QMessageBox::information(this, "Recherche", "Aucun résultat trouvé pour la valeur " + valeurRecherchee + ".");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la recherche : " + query.lastError().text());
    }

}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();

    // Récupérer les données de la ligne sélectionnée
    int idchambre = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();
    QString etat = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();
    QString type = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();
    float tarif = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toFloat();// Tarif en float
    QString id_res;
    QSqlQuery query;
    query.prepare("Select id_reservation from GS_RESERVATION where idchambre=:id");
    query.bindValue(":id", idchambre);

    if (query.exec()) {
        qDebug() << "Query executed successfully!";
        if (query.next()) {
            id_res = query.value(0).toString();
            qDebug() << "id_res: " << id_res;
        } else {
            qDebug() << "No result found for idchambre: " << idchambre;
        }
    } else {
        qDebug() << "Query execution failed: " << query.lastError().text();
    }
    // Remplir les champs avec les données récupérées
    ui->lineEdit_ID->setText(QString::number(idchambre));
    ui->comboBox_etat->setCurrentText(etat);  // Remplir comboBox avec l'état
    ui->comboBox_type->setCurrentText(type);  // Remplir comboBox avec le type
    ui->lineEdit_T->setText(QString::number(tarif, 'f', 2));
    ui->comboBox->setCurrentText(id_res);

}

void MainWindow::on_qrcode_button_clicked()
{

    // Récupération des informations de la chambre sélectionnée
    QString idChambre = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toString();
    QString etat = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 1)).toString();
    QString type = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 2)).toString();
    QString tarif = QString::number(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 3)).toFloat(), 'f', 2);

    // Création de la chaîne de texte pour le QR code
    QString text = "ID Chambre: " + idChambre +
                   "\nÉtat: " + etat +
                   "\nType: " + type +
                   "\nTarif: " + tarif;

    using namespace qrcodegen;

    // Création du QR code
    QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);
    qint32 sz = qr.getSize();
    QImage im(sz, sz, QImage::Format_RGB32);
    QRgb black = qRgb(0, 0, 0);
    QRgb white = qRgb(255, 255, 255);

    // Génération de l'image du QR code
    for (int y = 0; y < sz; y++) {
        for (int x = 0; x < sz; x++) {
            im.setPixel(x, y, qr.getModule(x, y) ? black : white);
        }
    }

    // Affichage du QR code dans l'interface
    ui->qr_code->setPixmap(QPixmap::fromImage(im.scaled(256, 256, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));

}

void MainWindow::on_tabWidget_currentChanged()
{
    // Configuration du son
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(1.0);  // Volume entre 0.0 et 1.0

    player->setSource(QUrl::fromLocalFile("C:/Users/HP/Downloads/intg/button.wav"));
    player->play();

    // Création du modèle de requêtes SQL
    QSqlQueryModel *model = new QSqlQueryModel();

    // Requêtes pour chaque type de chambre
    model->setQuery("select * from gs_chambre where TYPE='double' ");
    int number1 = model->rowCount();

    model->setQuery("select * from gs_chambre where TYPE='famile' ");  // Utilisez l'orthographe correcte
    int number2 = model->rowCount();

    model->setQuery("select * from gs_chambre where TYPE='suite' ");
    int number3 = model->rowCount();

    model->setQuery("select * from gs_chambre where TYPE='simple' ");
    int number4 = model->rowCount();

    // Calcul du total et des pourcentages
    int total = number1 + number2 + number3 + number4;

    QString a = QString("double " + QString::number((number1 * 100) / total, 'f', 2) + "%");
    QString b = QString("famile " + QString::number((number2 * 100) / total, 'f', 2) + "%");
    QString c = QString("suite " + QString::number((number3 * 100) / total, 'f', 2) + "%");
    QString d = QString("simple " + QString::number((number4 * 100) / total, 'f', 2) + "%");

    // Création de la série de données pour le graphique en camembert
    QPieSeries *series = new QPieSeries();
    series->append(a, number1);
    series->append(b, number2);
    series->append(c, number3);
    series->append(d, number4);

    if (number1 != 0) series->slices().at(0)->setLabelVisible();
    if (number2 != 0) series->slices().at(1)->setLabelVisible();
    if (number3 != 0) series->slices().at(2)->setLabelVisible();
    if (number4 != 0) series->slices().at(3)->setLabelVisible();

    // Création du graphique et configuration
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage Par TYPE : Nombre de chaque type de chambre " + QString::number(total));
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Suppression du layout précédent (s'il y en a un) et ajout du nouveau graphique
    if (ui->label_type->layout() != nullptr) {
        delete ui->label_type->layout();
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->label_type);
    layout->addWidget(chartView);
    ui->label_type->setLayout(layout);
}

void MainWindow::box()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString query = "SELECT ID_RESERVATION FROM GS_RESERVATION";
    model->setQuery(query);
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(0);

}


void MainWindow::on_pushButton_SMS_clicked()
{

    QNetworkAccessManager* manager = new QNetworkAccessManager();

    // Twilio API Credentials
    QString accountSID = "AC0ab85d030d910067416bc0204c8138db";
    QString authToken = "54a304e86d63b45f987ecb5f37bc6550";
    QString fromNumber = "+14243427425"; // Twilio number

    // Selected reservation ID
    QString id = ui->comboBox->currentText();
    qDebug() << "Selected ID from comboBox:" << id;

    // Query to fetch reservation details
    QSqlQuery query;
    query.prepare("SELECT NUMT, MONTANT_TOTAL, IDCHAMBRE FROM GS_RESERVATION WHERE ID_RESERVATION = :id");
    query.bindValue(":id", id);

    QString numm, montant, idch, type;

    if (query.exec() && query.next()) {
        numm = query.value(0).toString();
        montant = query.value(1).toString();
        idch = query.value(2).toString();
        qDebug() << "Query 1 Results - NUMT:" << numm << ", MONTANT_TOTAL:" << montant << ", IDCHAMBRE:" << idch;
    } else {
        qDebug() << "Query 1 failed or no results:" << query.lastError().text();
        return;
    }

    // Query to fetch room type
    QSqlQuery query2;
    query2.prepare("SELECT TYPE FROM GS_CHAMBRE WHERE IDCHAMBRE = :id");
    query2.bindValue(":id", idch);

    if (query2.exec() && query2.next()) {
        type = query2.value(0).toString();
        qDebug() << "Query 2 Result - TYPE:" << type;
    } else {
        qDebug() << "Query 2 failed or no results:" << query2.lastError().text();
        return;
    }

    QString toNumber = "+216" + numm; // Recipient number
    QString message = "Hello, votre chambre est le numero : " + idch +
                      " \nLe montant total : " + montant +
                      " \nType : " + type;

    QString url = QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json").arg(accountSID);
    QNetworkRequest request{QUrl(url)};

    // Add headers
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray credentials = QString("%1:%2").arg(accountSID, authToken).toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + credentials);

    // Data to send
    QUrlQuery params;
    params.addQueryItem("From", fromNumber);
    params.addQueryItem("To", toNumber);
    params.addQueryItem("Body", message);

    // Send the request
    QNetworkReply* reply = manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "SMS sent successfully!";
        } else {
            qDebug() << "Failed to send SMS:" << reply->errorString();
        }
        reply->deleteLater();
    });
}






/*void MainWindow::on_pushButton_exporter_2_clicked()
{
    int idchambre=ui->lineEdit_ID->text().toInt();
    QString etat =ui->comboBox_etat->currentText();
    QString type =ui->comboBox_type->currentText();
    float tarif = ui->lineEdit_T->text().toFloat();
    QString id = ui->comboBox->currentText();
    QSqlQuery query;
    QString date_debut,date_fin;
    query.prepare("Select date_dedut,date_fin from GS_RESERVATION where id_reservation=:id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Query executed successfully!";
        if (query.next()) {
            date_debut = query.value(0).toString();
            date_fin = query.value(1).toString();
            qDebug() << "id_res: " << id;
            createPDF(idchambre, etat, type, tarif, id, date_debut, date_fin);
        } else {
            qDebug() << "No result found for idchambre: " << id;
        }
    } else {
        qDebug() << "Query execution failed: " << query.lastError().text();
    }
}*/


/*void MainWindow::createPDF(int idchambre, const QString& etat, const QString& type, float tarif, const QString& id, const QString& date_debut, const QString& date_fin) {
    // Choose a location to save the PDF
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save PDF", "", "*.pdf");
    if (filePath.isEmpty())
        return; // If user cancels

    // Create the PDF Writer
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4); // Set page size to A4
    pdfWriter.setResolution(300); // Set resolution for better quality

    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        qDebug() << "Failed to open PDF writer.";
        return;
    }

    // Set up font and styles
    QFont font("Arial", 12);
    painter.setFont(font);

    // Write content to the PDF
    int y = 100; // Vertical position for text
    int lineHeight = 100; // Spacing between lines

    painter.drawText(30, y, "Chambre Details:");
    y += lineHeight;
    painter.drawText(30, y, "ID Chambre: " + QString::number(idchambre));
    y += lineHeight;
    painter.drawText(50, y, "Etat: " + etat);
    y += lineHeight;
    painter.drawText(50, y, "Type: " + type);
    y += lineHeight;


    // Convert tarif to QString with two decimals
    QString tarifString = QString::number(tarif, 'f', 2); // Format as float with 2 decimals
    painter.drawText(50, y, "Tarif: " + tarifString);
    y += lineHeight;

    // Set text color to green for "Reservation Details"
    painter.setPen(Qt::green);

    // Restore text color to default (black) for the rest of the content
    painter.setPen(Qt::black);
    painter.drawText(50, y, "Date Debut: " + date_debut);
    y += lineHeight;
    painter.drawText(50, y, "Date Fin: " + date_fin);
    y += lineHeight;

    // Finish and save
    painter.end();

    qDebug() << "PDF saved successfully at: " << filePath;
}*/


/*void MainWindow::readDataFromArduino()
{
    QString data = A.read_from_arduino();
    qDebug() << "rfid : " << data;
    QDate cd = QDate::currentDate();
    QSqlQuery query;
    query.prepare("SELECT idchambre FROM GS_CHAMBRE WHERE IDRFID = :rfid_id ");
    query.bindValue(":rfid_id", data);
    if (query.exec()) {
        if (query.next()) {
            QString idChambreDB = query.value(0).toString();

            // Vérification des dates de réservation
            QSqlQuery reservationQuery;
            reservationQuery.prepare("SELECT date_fin FROM GS_RESERVATION WHERE idchambre = :idchambre");
            reservationQuery.bindValue(":idchambre", idChambreDB);
            if (reservationQuery.exec() && reservationQuery.next()) {
                //QDate dateDebutDB = reservationQuery.value("date_debut").toDate();
                QDate dateFinDB = reservationQuery.value(0).toDate();

                if (cd > dateFinDB) {
                    ui->label_message->setText("La date de réservation de cette chambre est terminée!");
                } else {
                    ui->label_message->setText("Votre chambre est ouverte");

                }
            } else {
                qDebug() << "Query execution failed: " << query.lastError().text();
            }
        } else {
            ui->label_message->setText(" IDchambre incorrect!");
        }
    } else {
        ui->label_message->setText("Erreur de requête SQL : " + query.lastError().text());
    }
}*/



// ************************************************ gs_reservation ******************************************************************************

void MainWindow::rafraichirTable()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM GS_RESERVATION", db);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur de requête:" << model->lastError();
    } else {
        qDebug() << "Nombre de lignes retournées:" << model->rowCount();
    }

    ui->tableView_2->setModel(model);  // Mettre à jour le modèle de la table
}

void MainWindow::on_comboBox_statut_activated(int index)
{
    // Implémentation pour ce slot
    qDebug() << "ComboBox Statut activated, index: " << index;
}

void MainWindow::on_comboBox_type_2_activated(int index)
{
    // Implémentation pour ce slot
    qDebug() << "ComboBox Type activated, index: " << index;
}

void MainWindow::on_comboBox_mode_activated(int index)
{
    // Implémentation pour ce slot
    qDebug() << "ComboBox Mode activated, index: " << index;
}







void MainWindow::on_annuler_clicked()
{
    // Réinitialiser les champs de l'interface
    ui->id_reservation->clear();
    ui->id_client->clear();
    ui->comboBox_type_2->setCurrentIndex(0);
    ui->date_debut->setDate(QDate::currentDate());
    ui->date_fin->setDate(QDate::currentDate());
    ui->comboBox_statut->setCurrentIndex(0);
    ui->Montant->clear();
    ui->comboBox_mode->setCurrentIndex(0);
    ui->Np->clear();
    rafraichirTable();

}







void MainWindow::on_supprimer_clicked()
{
    // Récupérer l'ID de la réservation à partir de l'interface utilisateur
    int id = ui->lineEdit_idReservation->text().toInt(); // Conversion de la chaîne en entier

    // Vérification si l'ID est valide (positif) et s'il a été saisi
    if (ui->lineEdit_idReservation->text().isEmpty() || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID de réservation valide.");
        return;
    }

    // Appel de la méthode supprimer via l'objet réservation
    bool test = Rtmp.supprimer(id); // Remplacer 'Rtmp' par l'instance correcte de votre objet

    // Affichage des messages en fonction du résultat
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
        rafraichirTable();  // Rafraîchir la table après la suppression
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }

    // Forcer un rafraîchissement de la tableView après suppression
    ui->tableView_2->reset();  // Cette méthode réinitialise le modèle et le rafraîchit
}




/*void MainWindow::oncomboBoxCritere(int index)
{
    switch (index)
    {
    case 0:
        ui->comboBoxCritere->setCurrentText("Montant");
        break;
    case 1:
        ui->comboBoxCritere->setCurrentText("statut");
        break;
    case 2:
        ui->comboBoxCritere->setCurrentText("date_debut");
        break;
    default :
        break;
    }
}*/
void MainWindow::on_modifier_clicked()
{
    int id_reservation = ui->id_reservation->text().toInt(); // Récupérer l'ID de la réservation à modifier

    // Vérifier si l'ID existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT * FROM GS_RESERVATION WHERE id_reservation = :id_reservation");
    query.bindValue(":id_reservation", id_reservation);
    query.exec();

    // Si l'ID existe, récupérer les données et les afficher dans les champs
    if (query.next()) {
        int id_client = query.value("id_client").toInt();
        int idchambre = ui->comboBox_idchambre->currentText().toInt();
        QString type_reservation = query.value("type_reservation").toString();
        QDate date_debut = query.value("date_debut").toDate();
        QDate date_fin = query.value("date_fin").toDate();
        int nb_personnes = query.value("nb_personnes").toInt();
        QString statut = query.value("statut").toString();
        double montant = query.value("montant").toDouble();
        QString mode_paiement = query.value("mode_paiement").toString();

        // Vérifiez si l'id_chambre existe dans gs_chambre avant de modifier
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM gs_chambre WHERE id_chambre = :idchambre");
        query.bindValue(":idchambre", idchambre);
        query.exec();
        query.next();
        if (query.value(0).toInt() == 0) {
            QMessageBox::warning(this, "Erreur", "L'ID de la chambre n'existe pas.");
            return;
        }

        // Afficher les données dans les champs
        ui->id_client->setText(QString::number(id_client));
        ui->comboBox_type_2->setCurrentText(type_reservation); // Assurez-vous de remplir le champ de type réservation
        ui->date_debut->setDate(date_debut);
        ui->date_fin->setDate(date_fin);
        ui->Np->setText(QString::number(nb_personnes));
        ui->comboBox_statut->setCurrentText(statut); // Statut dans comboBox
        ui->Montant->setText(QString::number(montant));
        ui->comboBox_mode->setCurrentText(mode_paiement); // Mode de paiement dans comboBox
    } else {
        // Si l'ID n'existe pas, afficher un message d'erreur
        QMessageBox::warning(this, "Erreur", "Aucune réservation trouvée avec cet ID.");
        return;
    }

    // Vérifier que la date de fin est après la date de début
    if (ui->date_debut->date() > ui->date_fin->date()) {
        QMessageBox::critical(this, "Erreur", "La date de fin doit être après la date de début.");
        return;
    }

    // Créer l'objet réservation avec les nouvelles valeurs
    reservation res(id_reservation,
                    ui->id_client->text().toInt(), // Conversion de QString à int
                    ui->comboBox_type_2->currentText(),
                    ui->date_debut->date(),
                    ui->date_fin->date(),
                    ui->Np->text().toInt(),
                    ui->comboBox_statut->currentText(),
                    ui->Montant->text().toDouble(),
                    ui->comboBox_mode->currentText());

    // Appeler la méthode modifier() pour appliquer les changements
    if (res.modifier(id_reservation)) {
        QMessageBox::information(this, "Succès", " la reservation est trouvée vous pouvez faire la modifictaion.");
    } else {
        QMessageBox::critical(this, "Erreur", "La modification a échoué. Vérifiez les données.");
    }
}


void MainWindow::on_trier_clicked()
{
    QString critere = ui->comboBoxCritere->currentText();  // Exemple: "date_debut", "montant", "statut"

    // Vérification que le critère est valide
    if (critere.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un critère de tri.");
        return;
    }

    // Création d'un objet reservation pour appeler la méthode trier
    reservation res(0, 0, "", QDate(), QDate(), 0, "", 0.0, "");  // Les paramètres peuvent être quelconques

    // Appel de la méthode trier avec le critère sélectionné
    QSqlQuery query = res.trier(critere);

    // Vérification du résultat de la requête de tri
    if (query.isActive()) {
        // Création d'un modèle pour afficher les résultats dans une QTableView
        QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery(std::move(query));  // Déplacement de la requête au lieu de la copie


        // Affichage du modèle dans une table
        ui->tableView_2->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors du tri des réservations.");
    }
}



void MainWindow::on_rechercher_clicked()
{
    /*// Récupérer le critère sélectionné dans le comboBox (id_reservation, id_client, montant)
    QString critere = ui->comboBox_criteria->currentText();

    // Récupérer la valeur saisie dans le champ de texte pour la recherche
    QString value = ui->lineEdit_searchValue->text();

    // Créer un objet reservation pour effectuer la recherche
    reservation res;

    // Appeler la méthode rechercher pour récupérer les résultats
    QSqlQueryModel* model = res.rechercher(critere, value);

    // Si des résultats sont trouvés (model->rowCount() > 0)
    if (model->rowCount() > 0) {
        // Afficher les résultats dans le QTableView
        ui->tableView_2->setModel(model);
    } else {
        // Sinon, afficher un message indiquant qu'aucune réservation n'a été trouvée
        QMessageBox::warning(this, "Recherche", "Réservation non trouvée.");
    }*/


    // Récupérer le critère sélectionné dans le comboBox (id_reservation, id_client, montant)
    QString critere = ui->comboBox_criteria->currentText();

    // Récupérer la valeur saisie dans le champ de texte pour la recherche
    QString value = ui->lineEdit_searchValue->text();

    // Créer un objet reservation pour effectuer la recherche
    reservation res;

    // Appeler la méthode rechercher pour récupérer les résultats
    QSqlQueryModel* model = res.rechercher(critere, value);

    // Si des résultats sont trouvés (model != nullptr et model->rowCount() > 0)
    if (model && model->rowCount() > 0) {
        // Afficher les résultats dans le QTableView
        ui->tableView_2->setModel(model);
    } else {
        // Sinon, afficher un message indiquant qu'aucune réservation n'a été trouvée
        QMessageBox::warning(this, "Recherche", "Réservation non trouvée.");
    }
}





void MainWindow::on_exporter_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return;
    }

    int id_reservation = ui->lineEdit_idReservation->text().toInt();

    reservation res;
    res.setIdReservation(id_reservation);
    res.setIdClient(ui->id_client->text().toInt());
    res.setTypeReservation(ui->comboBox_type->currentText());
    res.setDateDebut(ui->date_debut->date());
    res.setDateFin(ui->date_fin->date());
    res.setNbPersonnes(ui->Np->text().toInt()); // Assurez-vous que c'est un QLineEdit
    res.setStatut(ui->comboBox_statut->currentText());
    res.setMontant(ui->Montant->text().toDouble()); // Assurez-vous que c'est un QLineEdit
    res.setModePaiement(ui->comboBox_mode->currentText());

    bool success = res.exporterPDF(filePath);
    if (success) {
        QMessageBox::information(this, "Succès", "Le fichier PDF a été enregistré avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'exportation du fichier PDF.");
    }

}

void MainWindow::on_ajouter_clicked()
{
    /*// Récupération des données du formulaire
    int id_reservation = ui->id_reservation->text().toInt();
    int id_client = ui->id_client->text().toInt();
    QString type_reservation = ui->comboBox_type_2->currentText();
    QDate date_debut = ui->date_debut->date();
    QDate date_fin = ui->date_fin->date();
    int nb_personnes = ui->Np->text().toInt();
    QString statut = ui->comboBox_statut->currentText();
    QString mode_paiement = ui->comboBox_mode->currentText();
    double montant = ui->Montant->text().toDouble();

    // Vérification de la saisie des données
    if (id_reservation == 0 || id_client == 0 || type_reservation.isEmpty() ||
        statut.isEmpty() || mode_paiement.isEmpty() || montant == 0.0) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    }

    // Vérification de l'existence de l'ID de réservation
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GS_RESERVATION WHERE id_reservation = :id_reservation");
    query.bindValue(":id_reservation", id_reservation);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de l'exécution de la requête : " + query.lastError().text());
        return;
    }

    bool idExists = false; // Variable pour vérifier l'existence de l'ID
    if (query.next()) {
        if (query.value(0).toInt() > 0) {
            idExists = true; // L'ID existe dans la base de données
        }
    }
    QSqlQuery query12;
    query12.prepare("SELECT COUNT(*) FROM GS_RESERVATION WHERE id_client = :id_client");
    query12.bindValue(":id_client", id_client);

    if (!query12.exec()) {
        QMessageBox::critical(nullptr, "Database Error", query12.lastError().text());
        return;
    }

    if (query12.next()) {
        int count = query12.value(0).toInt();
        if (count > 3) {
            QMessageBox::information(nullptr, "Remise", "Ce client a droit à une remise de 10% !");
                montant=montant-montant*0.1;

        } else {
            QMessageBox::information(nullptr, "Aucune réduction", "Ce client n'est pas éligible à une réduction.");
        }
    }
    // Création de l'objet réservation
    reservation newRes(id_reservation, id_client, type_reservation, date_debut, date_fin,
                       nb_personnes, statut, montant, mode_paiement);

    bool test;
    if (idExists) {
        // Si l'ID existe, affichage d'un message d'erreur
        QMessageBox::critical(this, "Erreur", "Cette ID de réservation existe déjà.");
    } else {
        // Si l'ID n'existe pas, on effectue l'ajout
        test = newRes.ajouter(); // Appel de la méthode ajouter pour insérer la réservation dans la base de données

        // Vérification du succès de l'ajout
        if (test) {
            QMessageBox::information(this, "Ajout", "Ajout effectué avec succès.");
            rafraichirTable();  // Rafraîchir la table pour afficher la nouvelle réservation
        } else {
            QMessageBox::critical(this, "Erreur", "Ajout non effectué.");
        }
    }

    // Rafraîchissement de la table des réservations
    ui->tableView_2->setModel(Rtmp.afficher()); // Actualiser l'affichage des réservations*/

    // Récupération des données du formulaire
    int id_reservation = ui->id_reservation->text().toInt();
    int id_client = ui->id_client->text().toInt();
    QString type_reservation = ui->comboBox_type_2->currentText();
    QDate date_debut = ui->date_debut->date();
    QDate date_fin = ui->date_fin->date();
    int nb_personnes = ui->Np->text().toInt();
    QString statut = ui->comboBox_statut->currentText();
    double montant = ui->Montant->text().toDouble();
    QString mode_paiement = ui->comboBox_mode->currentText();

    // Validation des données avant l'ajout
    if (id_reservation <= 0 || id_client <= 0 || montant <= 0 || nb_personnes <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    }

    if (date_debut > date_fin) {
        QMessageBox::critical(this, "Erreur", "La date de début doit être avant la date de fin.");
        return;
    }

    // Création d'une nouvelle réservation
    reservation newReservation(id_reservation, id_client, type_reservation, date_debut, date_fin,
                               nb_personnes, statut, montant, mode_paiement);

    // Appel de la méthode ajouter()
    if (newReservation.ajouter()) {
        QMessageBox::information(this, "Succès", "Réservation ajoutée avec succès.");
        rafraichirTable(); // Mise à jour de l'affichage dans le tableau
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la réservation.");
    }

    // Réinitialisation des champs après l'ajout
    on_annuler_clicked();
}

void MainWindow::on_enregistrer_clicked()
{
    // Récupérer les nouvelles valeurs des champs
    int id_reservation = ui->id_reservation->text().toInt();
    int id_client = ui->id_client->text().toInt();
    QString type_reservation = ui->comboBox_type_2->currentText();
    QDate date_debut = ui->date_debut->date();
    QDate date_fin = ui->date_fin->date();
    int nb_personnes = ui->Np->text().toInt();
    QString statut = ui->comboBox_statut->currentText();
    QString mode_paiement = ui->comboBox_mode->currentText();
    double montant = ui->Montant->text().toDouble();

    // Vérifier si tous les champs sont remplis (contrôle de saisie)
    if (type_reservation.isEmpty() || statut.isEmpty() || mode_paiement.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Vérification que la date de fin est après la date de début
    if (date_debut > date_fin) {
        QMessageBox::critical(this, "Erreur", "La date de fin doit être après la date de début.");
        return;
    }

    // Vérification des valeurs numériques (id_client, nb_personnes, montant)
    if (id_client <= 0 || nb_personnes <= 0 || montant <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir des valeurs valides pour les champs numériques.");
        return;
    }

    // Vérification de l'existence de la réservation dans la base de données
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT COUNT(*) FROM GS_RESERVATION WHERE id_reservation = :id_reservation");
    queryCheck.bindValue(":id_reservation", id_reservation);
    queryCheck.exec();

    if (queryCheck.next() && queryCheck.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Erreur", "La réservation avec cet ID n'existe pas.");
        return;
    }

    // Mettre à jour la réservation dans la base de données
    QSqlQuery query;
    query.prepare("UPDATE GS_RESERVATION SET id_client = :id_client, type_reservation = :type_reservation, "
                  "date_debut = :date_debut, date_fin = :date_fin, nb_personnes = :nb_personnes, "
                  "statut = :statut, montant = :montant, mode_paiement = :mode_paiement "
                  "WHERE id_reservation = :id_reservation");

    query.bindValue(":id_reservation", id_reservation);
    query.bindValue(":id_client", id_client);
    query.bindValue(":type_reservation", type_reservation);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);
    query.bindValue(":nb_personnes", nb_personnes);
    query.bindValue(":statut", statut);
    query.bindValue(":mode_paiement", mode_paiement);
    query.bindValue(":montant", montant);


    // Exécuter la requête
    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Modification réussie !");
    } else {
        QMessageBox::warning(this, "Erreur", "La modification a échoué. Erreur : " + query.lastError().text());
    }
}
/*void MainWindow::alerte()
{


    QSqlQuery query;
    QStringList annulledIds;

    // SQL query to get id_reservation where statut is 'annulée'
    if (query.exec("SELECT id_reservation FROM reservation WHERE statut = 'annulée'")) {
        // Collect the ids into a list
        while (query.next()) {
            annulledIds << query.value(0).toString();
        }

        // If there are any annulled reservations, show a notification
        if (!annulledIds.isEmpty()) {
            QString message = "Les réservations suivantes sont annulées:\n" + annulledIds.join(", ");

            // Display notification using QSystemTrayIcon
            QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
            trayIcon->setIcon(QIcon("C:/Users/21621/Downloads/R.png")); // Replace with your icon path
            trayIcon->show(); // Show the tray icon

            trayIcon->showMessage("Alerte: Annulation",
                                  message,
                                  QSystemTrayIcon::Warning,
                                  5000); // Duration in milliseconds
        }
    } else {
        // Show an error if the query fails
        QMessageBox::critical(nullptr, "Database Error", query.lastError().text());
    }
}*/

void MainWindow::on_pushButton_statistiques_clicked()
{


    // Création du modèle de requêtes SQL
    QSqlQueryModel *model = new QSqlQueryModel();

    // Requêtes pour chaque type de réservation
    model->setQuery("SELECT * FROM GS_RESERVATION WHERE TYPE_RESERVATION='Chambre'");
    int number1 = model->rowCount();

    model->setQuery("SELECT * FROM GS_RESERVATION WHERE TYPE_RESERVATION='Restaurant'");
    int number2 = model->rowCount();

    model->setQuery("SELECT * FROM GS_RESERVATION WHERE TYPE_RESERVATION='Parking'");
    int number3 = model->rowCount();

    // Calcul du total
    int total = number1 + number2 + number3;

    // Éviter la division par zéro
    if (total == 0) {
        QMessageBox::warning(this, "Aucune réservation", "Il n'y a pas de données pour afficher les statistiques.");
        return;
    }

    // Calcul des pourcentages
    QString a = QString("Chambre: %1%").arg((number1 * 100.0) / total, 0, 'f', 2);
    QString b = QString("Restaurant: %1%").arg((number2 * 100.0) / total, 0, 'f', 2);
    QString c = QString("Parking: %1%").arg((number3 * 100.0) / total, 0, 'f', 2);

    // Création de la série pour le graphique en camembert
    QPieSeries *series = new QPieSeries();
    series->append(a, number1);
    series->append(b, number2);
    series->append(c, number3);

    // Rendre les labels visibles uniquement si le nombre est non nul
    if (number1 != 0) series->slices().at(0)->setLabelVisible();
    if (number2 != 0) series->slices().at(1)->setLabelVisible();
    if (number3 != 0) series->slices().at(2)->setLabelVisible();

    // Configuration du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage par Type de Réservation (Total: " + QString::number(total) + ")");
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Supprimer le layout précédent (s'il existe) et ajouter le nouveau graphique
    if (ui->graphWidget->layout() != nullptr) {
        delete ui->graphWidget->layout();
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->graphWidget);
    layout->addWidget(chartView);
    ui->graphWidget->setLayout(layout);

    QMessageBox::information(this, "Statistiques", "Graphique mis à jour avec succès.");
}





/*void MainWindow::setupTimer() {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateObstacleStatus);
    timer->start(100);  // Lire les données toutes les 0.5 seconde, essayer avec un délai plus court
}


void MainWindow::updateObstacleStatus() {
    QByteArray data = arduino->read_from_arduino();  // Lire les données de l'Arduino
    if (!data.isEmpty()) {
        qDebug() << "Données reçues : " << data;
        QString message = QString::fromUtf8(data.trimmed());  // Convertir en chaîne de caractères et enlever les espaces inutiles
        qDebug() << "Message reçu : " << message;

        // Détection de l'obstacle et ouverture/fermeture de la barrière
        if (message.contains("Voiture détectée")) {
            // Incrémenter le compteur de détections
            detection_count++;

            // Décrémenter les places disponibles et ouvrir la barrière
            if (placesDisponibles > 0) {
                placesDisponibles--;
            }

            arduino->write_to_arduino("OPEN\n");  // Ouvrir la barrière

            // Mettre à jour l'affichage
            if (placesDisponibles == 0) {
                ui->label1->setText("Aucune place disponible.");
            } else {
                ui->label1->setText(QString::number(placesDisponibles) + " place(s) disponible(s).");
            }

            // Vérifier si la limite de détection de voiture est atteinte
            if (detection_count >= 5) {
                ui->label1->setText("Aucune place disponible.");
            }
        }
        else if (message.contains("Aucun obstacle")) {
            // Réinitialiser le compteur de détections si aucune voiture n'est détectée
            detection_count = 0;
            // Fermer la barrière
            arduino->write_to_arduino("CLOSE\n");
            ui->label1->setText("Aucune voiture détectée.");
        }
    } else {
        qDebug() << "Aucune donnée reçue.";
    }
}*/



void MainWindow::on_comboBoxCritere_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->comboBoxCritere->setCurrentText("Montant");
        break;
    case 1:
        ui->comboBoxCritere->setCurrentText("statut");
        break;
    case 2:
        ui->comboBoxCritere->setCurrentText("date_debut");
        break;
    default :
        break;
    }
}





void MainWindow::on_comboBox_criteria_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->comboBox_criteria->setCurrentText("id_reservation");
        break;
    case 1:
        ui->comboBox_criteria->setCurrentText("id_client");
        break;
    case 2:
        ui->comboBox_criteria->setCurrentText("montant");
        break;
    default :
        break;
    }
}

