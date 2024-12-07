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
#include "financier.h"

#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QTableView>
#include <QFileDialog>
#include <QTextDocument>
#include <QDebug>
#include<QDesktopServices>

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


#include "reservation.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(readDataFromArduino())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données).

    ui->lineEdit_supp->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_ID->setValidator(new QIntValidator(0,9999,this));
    connect(ui->pushButton_exporter_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_exporter_2_clicked);
    connect(ui->lineEdit_ID, &QLineEdit::editingFinished, this, &MainWindow::on_lineEdit_ID_editingFinished);
    connect(ui->pushButton_tri, &QPushButton::clicked, this, &MainWindow::on_pushButton_tri_clicked);
    //connect(A.getserial(), &QSerialPort::readyRead, this, &MainWindow::readDataFromArduino);

    ui->comboBox_trier->addItem("etat");
    ui->comboBox_trier->addItem("type");
    ui->comboBox_trier->addItem("tarif");
    ui->tableView->setModel(CHtmp.afficher());

    ui->lineEdit_ID1->setValidator(new QIntValidator(0, 99999, this));

    // Initialisation des comboBox
    ui->comboBox_type_reservation->addItems({"Chambre", "Restaurant", "Parking"});
    ui->comboBox_mode_paiement->addItems({"carte bancaire", "espéces", "Virement"});

    // Charger les réservations dans le tableView
    ui->tableView_2->setModel(resTmp.afficher1());
    ui->tableView_trr->setModel(ETMP.afficher3());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    // Exemple de mise à jour d'un label dans l'interface utilisateur
    ui->label->setText("Mise à jour du label");
}

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
    // Récupérer l'ID de la chambre à supprimer à partir de lineEdit_supp
    int idchambre = ui->lineEdit_supp->text().toInt();

    // Vérifier si un ID valide a été saisi
    if (idchambre <= 0) {
        QMessageBox::warning(this, "Avertissement", "Veuillez entrer un ID valide.");
        return;
    }

    // Appeler la fonction de suppression
    bool test = CHtmp.supprimer(idchambre);

    if (test) {
        QMessageBox::information(this, "Succès", "Chambre supprimée avec succès.");

        // Effacer le contenu de lineEdit_supp
        ui->lineEdit_supp->clear();

        // Mettre à jour le tableView pour refléter les changements
        ui->tableView->setModel(CHtmp.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression. Vérifiez que l'ID existe.");
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

// pour modifier

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

// statistique
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
    QString authToken = "623afbbf604062b04a875336cbba6bec";
    QString fromNumber = "+14243427425"; // Twilio number

    // Selected reservation ID
    QString id = ui->comboBox->currentText();
    qDebug() << "Selected ID from comboBox:" << id;

    // Query to fetch reservation details
    QSqlQuery query;
    query.prepare("SELECT NUMT, MONTANT, IDCHAMBRE FROM GS_RESERVATION WHERE ID_RESERVATION = :id");
    query.bindValue(":id", id);

    QString numm, montant, idch, type;

    if (query.exec() && query.next()) {
        numm = query.value(0).toString();
        montant = query.value(1).toString();
        idch = query.value(2).toString();
        qDebug() << "Query 1 Results - NUMT:" << numm << ", MONTANT:" << montant << ", IDCHAMBRE:" << idch;
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


void MainWindow::on_pushButton_exporter_2_clicked()
{
    int idchambre=ui->lineEdit_ID->text().toInt();
    QString etat =ui->comboBox_etat->currentText();
    QString type =ui->comboBox_type->currentText();
    float tarif = ui->lineEdit_T->text().toFloat();
    QString id = ui->comboBox->currentText();
    QSqlQuery query;
    QString date_debut,date_fin;
    query.prepare("Select DATE_DEBUT,DATE_FIN from GS_RESERVATION where id_reservation=:id");
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



}


void MainWindow::createPDF(int idchambre, const QString& etat, const QString& type, float tarif, const QString& id, const QString& date_debut, const QString& date_fin) {
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
    /*painter.drawText(50, y, "Tarif: " + QString::number(tarif));
    y += lineHeight;*/

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
}


void MainWindow::readDataFromArduino()
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
                    ui->label_message->setText("La date de réservation de cette chambre est terminée !");
                } else {
                    ui->label_message->setText("Votre chambre est ouverte !");

                }
            } else {
                qDebug() << "Query execution failed: " << query.lastError().text();
            }
        } else {
            ui->label_message->setText("Erreur : IDchambre non trouvé!");
        }
    } else {
        ui->label_message->setText("Erreur de requête SQL : " + query.lastError().text());
    }
}

//********************************************gs_reservation *******************************************************

void MainWindow::on_pushButton_Ajouter1_clicked()
{
    int id_reservation = ui->lineEdit_ID1->text().toInt();
    int id_client = ui->lineEdit_ClientID->text().toInt();
    QString type_reservation = ui->comboBox_type_reservation->currentText();
    QDate date_debut = ui->dateEdit_Debut->date();
    QDate date_fin = ui->dateEdit_Fin->date();
    int nb_personnes = ui->lineEdit_NbPersonnes->text().toInt();
    QString statut = ui->comboBox_statut->currentText();
     QString mode_paiement = ui->comboBox_mode_paiement->currentText();
    double montant = ui->lineEdit_Montant->text().toDouble();
    int numt = ui->lineEdit_Numt->text().toInt();

    // Validation des champs
    if (id_reservation <= 0 || id_client <= 0 || type_reservation.isEmpty() || statut.isEmpty() || montant <= 0 || mode_paiement.isEmpty() || date_debut.isNull() || date_fin.isNull() || date_debut > date_fin) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer des informations valides. Assurez-vous que les dates sont correctes.");
        return;
    }

    // Vérification de l'existence de l'ID
    int dummyIdClient;
    QString dummyTypeReservation, dummyStatut, dummyModePaiement;
    QDate dummyDateDebut, dummyDateFin;
    int dummyNbPersonnes, dummyNumt;
    double dummyMontant;

    if (getReservationData(id_reservation, dummyIdClient, dummyTypeReservation, dummyDateDebut, dummyDateFin, dummyNbPersonnes, dummyStatut, dummyModePaiement, dummyMontant, dummyNumt)) {
        // Si l'ID est trouvé, on effectue une modification
        QSqlQuery query;
        query.prepare("UPDATE gs_reservation SET id_client = :id_client, type_reservation = :type_reservation, date_debut = :date_debut, date_fin = :date_fin, nb_personnes = :nb_personnes, statut = :statut, mode_paiement = :mode_paiement, montant = :montant, numt = :numt WHERE id_reservation = :id_reservation");
        query.bindValue(":id_reservation", id_reservation);
        query.bindValue(":id_client", id_client);
        query.bindValue(":type_reservation", type_reservation);
        query.bindValue(":date_debut", date_debut);
        query.bindValue(":date_fin", date_fin);
        query.bindValue(":nb_personnes", nb_personnes);
        query.bindValue(":statut", statut);
        query.bindValue(":mode_paiement", mode_paiement);
        query.bindValue(":montant", montant);
        query.bindValue(":numt", numt);

        if (query.exec()) {
            QMessageBox::information(this, "Modification", "Modification effectuée avec succès.");
            ui->tableView_2->setModel(resTmp.afficher1());
            clearFields1();
        } else {
            qDebug() << "Erreur lors de la modification : " << query.lastError().text();
            QMessageBox::critical(this, "Erreur", "Échec de la modification.");
        }
    } else {
        // Si l'ID n'est pas trouvé, on effectue un ajout
        reservation res(id_reservation, id_client, type_reservation, date_debut, date_fin, nb_personnes, statut, mode_paiement, montant,numt);
        if (res.ajouter1()) {
            QMessageBox::information(this, "Ajout", "Ajout effectué avec succès.");
            ui->tableView_2->setModel(resTmp.afficher1());
            clearFields1();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout.");
        }
    }
}

void MainWindow::on_pushButton_Supprimer1_clicked()
{
    QString critere = ui->comboBox_trier_3->currentText();
    QString valeurRecherchee = ui->lineEdit_Rech2->text();

    if (critere == "id_reservation") {
        int id_reservation = valeurRecherchee.toInt();

        // Vérifiez si l'ID de la réservation existe avant de supprimer
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM gs_reservation WHERE id_reservation = :id_reservation");
        query.bindValue(":id_reservation", id_reservation);
        query.exec();

        if (query.next() && query.value(0).toInt() > 0) {
            // L'ID existe, procéder à la suppression
            reservation res;
            bool test = res.supprimer1(id_reservation);
            if (test) {
                ui->tableView_2->setModel(res.afficher1());
                QMessageBox::information(this, QObject::tr("Succès"),
                                         QObject::tr("Suppression effectuée avec succès."),
                                         QMessageBox::Ok);
                // Effacer les champs après la suppression
                ui->lineEdit_Rech2->clear();
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
                             QObject::tr("Veuillez sélectionner 'id_reservation' comme critère de recherche."),
                             QMessageBox::Ok);
    }
}


void MainWindow::clearFields1()
{
    ui->lineEdit_ID1->clear();
    ui->lineEdit_ClientID->clear();
    ui->comboBox_type_reservation->setCurrentIndex(-1);
    ui->dateEdit_Debut->clear();
    ui->dateEdit_Fin->clear();
    ui->lineEdit_NbPersonnes->clear();
    ui->comboBox_statut->setCurrentIndex(-1);
    ui->comboBox_mode_paiement->setCurrentIndex(-1);
    ui->lineEdit_Montant->clear();
    ui->lineEdit_Numt->clear();


}
bool MainWindow::getReservationData(const int &id_reservation, int &id_client, QString &type_reservation, QDate &date_debut, QDate &date_fin, int &nb_personnes, QString &statut, QString &mode_paiement, double &montant, int &numt)
{
    QSqlQuery query;
    query.prepare("SELECT id_client, type_reservation, date_debut, date_fin, nb_personnes, statut, mode_paiement, montant, numt FROM gs_reservation WHERE id_reservation = :id_reservation");
    query.bindValue(":id_reservation", id_reservation);

    if (query.exec() && query.next()) {
        id_client = query.value("id_client").toInt();
        type_reservation = query.value("type_reservation").toString();
        date_debut = query.value("date_debut").toDate();
        date_fin = query.value("date_fin").toDate();
        nb_personnes = query.value("nb_personnes").toInt();
        statut = query.value("statut").toString();
        mode_paiement = query.value("mode_paiement").toString();
        montant = query.value("montant").toDouble();
        numt = query.value("numt").toInt();
        return true;
    }
    return false;
}


bool MainWindow::loadReservationData(int id_reservation)
{
    int id_client, nb_personnes, numt;
    QString type_reservation, statut, mode_paiement;
    QDate date_debut, date_fin;
    double montant;

    // Récupération des données de réservation
    if (getReservationData(id_reservation, id_client, type_reservation, date_debut, date_fin, nb_personnes, statut, mode_paiement, montant, numt)) {
        // Mise à jour des champs de l'interface utilisateur
        ui->lineEdit_ClientID->setText(QString::number(id_client));
        ui->comboBox_type_reservation->setCurrentText(type_reservation);
        ui->dateEdit_Debut->setDate(date_debut);
        ui->dateEdit_Fin->setDate(date_fin);
        ui->lineEdit_NbPersonnes->setText(QString::number(nb_personnes));
        ui->comboBox_statut->setCurrentText(statut);
        ui->comboBox_mode_paiement->setCurrentText(mode_paiement);
        ui->lineEdit_Montant->setText(QString::number(montant, 'f', 2));
        ui->lineEdit_Numt->setText(QString::number(numt));
        return true;
    }
    return false;
}

void MainWindow::on_lineEdit_IDReservation_editingFinished()
{
    int id_reservation = ui->lineEdit_ID1->text().toInt();
    if (id_reservation > 0) {
        loadReservationData(id_reservation);
    }
}

void MainWindow::on_pushButton_Annuler1_clicked()
{
    ui->lineEdit_ID1->clear();
    ui->comboBox_type_reservation->setCurrentIndex(-1);
    ui->lineEdit_NbPersonnes->clear();
    ui->comboBox_statut->setCurrentIndex(-1);
    ui->lineEdit_Montant->clear();
}

void MainWindow::on_pushButton_tri1_2_clicked()
{
    QString triOption = ui->pushButton_tri1->currentText(); // Récupère l'option de tri
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (triOption == "Montant") {
        query.prepare("SELECT * FROM reservation ORDER BY montant ASC, id_reservation ASC");
    } else if (triOption == "statut") {
        query.prepare("SELECT * FROM reservation ORDER BY statut ASC, id_reservation ASC");
    } else if (triOption == "date_debut") {
        query.prepare("SELECT * FROM reservation ORDER BY date_debut ASC, id_reservation ASC");
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une option de tri valide.");
        return;
    }

    if (query.exec()) {
        model->setQuery(std::move(query));
        ui->tableView_2->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec du tri : " + query.lastError().text());
    }
}
void MainWindow::on_pushButton_Recherche1_clicked()
{
    QString critere = ui->comboBox_trier_3->currentText(); // Utiliser comboBox_trier_3 pour la sélection du critère
    QString valeurRecherchee = ui->lineEdit_Rech2->text();

    // Vérifiez si la valeur entrée est vide
    if (valeurRecherchee.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur pour la recherche.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (critere == "id_reservation") {
        // Recherche par ID de réservation
        query.prepare("SELECT * FROM gs_reservation WHERE id_reservation = :valeur");
        query.bindValue(":valeur", valeurRecherchee);
    } else if (critere == "id_client") {
        // Recherche par ID de client
        query.prepare("SELECT * FROM gs_reservation WHERE id_client = :valeur");
        query.bindValue(":valeur", valeurRecherchee);
    } else if (critere == "montant") {
        // Recherche par montant (avec tolérance)
        bool conversionOk;
        double montant = valeurRecherchee.toDouble(&conversionOk);

        if (!conversionOk) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer un montant valide (format : 150.25).");
            return;
        }

        // Utilisation d'une plage pour éviter les problèmes de précision
        double tolerance = 0.01;
        double minMontant = montant - tolerance;
        double maxMontant = montant + tolerance;

        query.prepare("SELECT * FROM gs_reservation WHERE montant BETWEEN :minMontant AND :maxMontant");
        query.bindValue(":minMontant", minMontant);
        query.bindValue(":maxMontant", maxMontant);
    } else {
        QMessageBox::warning(this, "Erreur", "Critère de recherche inconnu.");
        return;
    }

    // Exécute la requête
    if (query.exec()) {
        model->setQuery(std::move(query));
        ui->tableView_2->setModel(model);

        // Vérifie si des résultats ont été trouvés
        if (model->rowCount() > 0) {
            // Applique une coloration verte aux lignes trouvées
            for (int row = 0; row < model->rowCount(); ++row) {
                for (int col = 0; col < model->columnCount(); ++col) {
                    ui->tableView_2->model()->setData(
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



void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    int row1 = index.row();  // Correction du nom de la fonction

    // Récupérer les données de la ligne sélectionnée
    int id_reservation = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 0)).toInt();
    int id_client = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 1)).toInt();
    QString type_reservation = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 2)).toString();
    QDate date_debut = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 3)).toDate();
    QDate date_fin = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 4)).toDate();
    int nb_personnes = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 5)).toInt();
    QString statut = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 6)).toString();
    QString mode_paiement = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 7)).toString();
    double montant = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 8)).toDouble();
    int numt = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row1, 9)).toInt();


    // Remplir les champs avec les données récupérées
    ui->lineEdit_ID1->setText(QString::number(id_reservation));
    ui->lineEdit_ID->setText(QString::number(id_client));
    ui->comboBox_type_reservation->setCurrentText(type_reservation);
    ui->dateEdit_Debut->setDate(date_debut);
    ui->dateEdit_Fin->setDate(date_fin);
    ui->lineEdit_NbPersonnes->setText(QString::number(nb_personnes));
    ui->comboBox_statut->setCurrentText(statut);
    ui->comboBox_mode_paiement->setCurrentText(mode_paiement);
    ui->lineEdit_Montant->setText(QString::number(montant, 'f', 2));
    ui->lineEdit_Numt->setText(QString::number(numt));

}


void MainWindow::on_tabWidget_currentChanged1()
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

    // Requêtes pour chaque type de réservation
    model->setQuery("SELECT * FROM gs_reservation WHERE type_reservation = 'Chambre'");
    int numberChambre = model->rowCount();

    model->setQuery("SELECT * FROM gs_reservation WHERE type_reservation = 'Restaurant'");
    int numberRestaurant = model->rowCount();

    model->setQuery("SELECT * FROM gs_reservation WHERE type_reservation = 'Parking'");
    int numberParking = model->rowCount();

    // Calcul du total et des pourcentages
    int total = numberChambre + numberRestaurant + numberParking;

    QString a = QString("Chambre " + QString::number((numberChambre * 100) / total, 'f', 2) + "%");
    QString b = QString("Restaurant " + QString::number((numberRestaurant * 100) / total, 'f', 2) + "%");
    QString c = QString("Parking " + QString::number((numberParking * 100) / total, 'f', 2) + "%");

    // Création de la série de données pour le graphique en camembert
    QPieSeries *series = new QPieSeries();
    series->append(a, numberChambre);
    series->append(b, numberRestaurant);
    series->append(c, numberParking);

    if (numberChambre != 0) series->slices().at(0)->setLabelVisible();
    if (numberRestaurant != 0) series->slices().at(1)->setLabelVisible();
    if (numberParking != 0) series->slices().at(2)->setLabelVisible();

    // Création du graphique et configuration
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage Par Type de Réservation : Nombre de chaque type de réservation " + QString::number(total));
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Suppression du layout précédent (s'il y en a un) et ajout du nouveau graphique
    if (ui->label_type2->layout() != nullptr) {
        delete ui->label_type2->layout();
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->label_type2);
    layout->addWidget(chartView);
    ui->label_type2->setLayout(layout);
}

void MainWindow::on_pushButton_exporterela_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return;
    }

    int id_reservation = ui->lineEdit_ID1->text().toInt();

    reservation res;
    res.setId_Reservation(id_reservation);
    res.setId_Client(ui->lineEdit_ClientID->text().toInt());
    res.setType_Reservation(ui->comboBox_type->currentText());
    res.setDate_Debut(ui->dateEdit_Debut->date());
    res.setDate_Fin(ui->dateEdit_Fin->date());
    res.setNb_Personnes(ui->lineEdit_NbPersonnes->text().toInt()); // Assurez-vous que c'est un QLineEdit
    res.setStatut(ui->comboBox_statut->currentText());
    res.setMontant(ui->lineEdit_Montant->text().toDouble()); // Assurez-vous que c'est un QLineEdit
    res.setMode_Paiement(ui->comboBox_mode_paiement->currentText());

    bool success = res.exporterPDF(filePath);
    if (success) {
        QMessageBox::information(this, "Succès", "Le fichier PDF a été enregistré avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'exportation du fichier PDF.");
    }
}


//****************************************GS_FINANCIER ****************************************************

void MainWindow::clearFields3() {
      ui->lineEdit_IDT->clear();
    ui->lineEdit_Desct->clear();
    ui->dateEditt->setDate(QDate::currentDate());
    ui->lineEdit_Montantt->clear();
    ui->comboBox_typet->setCurrentIndex(0);
    ui->comboBox_modet->setCurrentIndex(0);

}

/*void MainWindow::on_sendButton_clicked()
{
    // Créer un objet de requête
    QSqlQuery query;

    // Définir la requête SQL
    QString sql = "SELECT NOM_SERVICE FROM SERVICES WHERE NOM_SERVICE = 'restaurant'";

    // Exécuter la requête
    if (!query.exec(sql)) {
        qDebug() << "Error: Failed to execute query -" << query.lastError().text();
        return; // Si la requête échoue, on arrête la fonction ici
    }

    // Si la requête est exécutée avec succès, récupérer le résultat
    QString nom_service;  // Variable pour stocker le nom du service

    // Vérifier si une ligne a été récupérée
    if (query.next()) {
        nom_service = query.value(0).toString() + " open 7-10am,12-16";  // Récupérer la valeur du premier champ (nom du service)
    }

    // Si le nom du service a été récupéré, l'envoyer à l'Arduino
    if (!nom_service.isEmpty()) {
        // Convertir la chaîne en QByteArray et envoyer à l'Arduino
        A.write_to_arduino(QByteArray::fromStdString(nom_service.toStdString()));
    } else {
        qDebug() << "Erreur : Aucun service trouvé.";
    }
}*/

/*void MainWindow::on_AJOUT_SERVICE_clicked()
{
    QString nomService = ui->lineEdit_SERVICE->text();
    f.ajouterService(nomService);
}*/


void MainWindow::on_pushButton_Ajouter3_clicked()
{
    int id= ui->lineEdit_IDT->text().toInt();
    QDate dateTransaction = ui->dateEditt->date();
    QString montant = ui->lineEdit_Montantt->text();
    QString desc = ui->lineEdit_Desct->text();
    QString type = ui->comboBox_typet->currentText();
    QString modePaiement = ui->comboBox_modet->currentText();

    // Ne pas passer l'ID car il est généré automatiquement
    financier f(id,dateTransaction, montant, desc, type, modePaiement);
    bool test = f.Ajouter3();  // L'ID sera géré par la base de données

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

    ui->tableView_trr->setModel(f.afficher3());
    clearFields3();  // Effacer les champs après l'ajout
}


void MainWindow::on_pushButton_2_clicked()
{
    // Récupérer la valeur sélectionnée dans comboBox_4
    QString critere = ui->comboBox_3->currentText();

    // Rafraîchir la table avec les données triées selon le critère choisi
    ui->tableView_trr->setModel(ETMP.tri_paiement(critere));
}


void MainWindow::on_pushButton_modifiertr_clicked()
{
    QDate dateTransaction =ui-> dateEditt->date();
    QString montant = ui->lineEdit_Montantt->text();
    int id = ui->lineEdit_IDT->text().toInt();
    QString desc = ui->lineEdit_Desct->text();
    QString type =ui->comboBox_typet->currentText();
    QString modePaiement =ui->comboBox_modet->currentText();
    financier f( id,dateTransaction,  montant ,  desc ,  type ,  modePaiement );
    bool test=f.modifier_paiement();

    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("modify effectué\n""click cancel to exit."),QMessageBox::Cancel);
        ui->tableView_trr->setModel(f.afficher3());
        if (id > 0) ui->lineEdit_IDT->clear();
        if (!montant.isEmpty()) ui->lineEdit_Montantt->clear();
        if (!desc.isEmpty()) ui->lineEdit_Desct->clear();
        if (!type.isEmpty()) ui->comboBox_typet->setCurrentText("");
        if (!modePaiement.isEmpty()) ui->comboBox_modet->setCurrentText("");
        if (dateTransaction.isValid()) ui->dateEditt->clear();

    }
}


void MainWindow::on_pushButton_6_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
    if (!fileName.isEmpty()) {
        financier f;
        QSqlQueryModel* model = f.afficher3();
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


void MainWindow::on_pushButton_historique_clicked()
{
    QString filePath = "C:/Users/user/Downloads/gestion chambre2/historique.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}




void MainWindow::on_pushButton_supt_clicked()
{
    int id = ui->lineEdit_suptr->text().toInt();
    bool test = ETMP.supprimer3(id); // Suppression de la transaction

    if (test) {

        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée et ."), QMessageBox::Cancel);


        // Actualiser la vue
        ui->tableView_trr->setModel(ETMP.afficher3());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Suppression non effectuée."), QMessageBox::Cancel);
    }

    //clearFields();
}


void MainWindow::on_pushButton_recherchetr_clicked()
{

        QString critere = ui->comboBox_2->currentText();
        QString valeurRecherchee = ui->lineEdit_recherchetr->text();

        // Vérifiez si la valeur entrée est vide
        if (valeurRecherchee.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur pour la recherche.");
            return;
        }

        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;

        if (critere == "id_transaction") {
            // Recherche par ID
            query.prepare("SELECT * FROM gs_financiere WHERE ID_TRANSACTION = :valeur");
            query.bindValue(":valeur", valeurRecherchee);
        } else if (critere == "Modepaiement") {
            // Recherche par tarif (avec tolérance)


            if (valeurRecherchee != "Espece" && valeurRecherchee != "Virement") {
                QMessageBox::warning(this, "Erreur", "Veuillez entrer un état valide (Disponible ou Occupee).");
                return;
            }

            query.prepare("SELECT * FROM gs_financiere WHERE mode_paiement = :valeur");
            query.bindValue(":valeur", valeurRecherchee);
        } else if (critere == "Type") {
            // Recherche par état
            if (valeurRecherchee != "Depense" && valeurRecherchee != "Revenu") {
                QMessageBox::warning(this, "Erreur", "Veuillez entrer un état valide (Disponible ou Occupee).");
                return;
            }

            query.prepare("SELECT * FROM gs_financiere WHERE Type = :valeur");
            query.bindValue(":valeur", valeurRecherchee);
        } else {
            QMessageBox::warning(this, "Erreur", "Critère de recherche inconnu.");
            return;
        }

        // Exécute la requête
        if (query.exec()) {
            model->setQuery(std::move(query));
            ui->tableView_trr->setModel(model);

            // Vérifie si des résultats ont été trouvés
            if (model->rowCount() > 0) {
                // Applique une coloration verte aux lignes trouvées
                for (int row = 0; row < model->rowCount(); ++row) {
                    for (int col = 0; col < model->columnCount(); ++col) {
                        ui->tableView_trr->model()->setData(
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


void MainWindow::on_tableView_trr_activated(const QModelIndex &index)
{
    QSqlQuery query;
    QString id = ui->tableView_trr->model()->data(index).toString(); // On utilise ID_TRANSACTION pour l'identification

    // Rechercher l'enregistrement uniquement par ID_TRANSACTION (car c'est une clé unique)
    query.prepare("SELECT * FROM gs_financiere WHERE ID_TRANSACTION = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next())
    {
        ui->lineEdit_IDT->setText(query.value("ID_TRANSACTION").toString());
        ui->lineEdit_Montantt->setText(query.value("MONTANT").toString());
        ui->lineEdit_Desct->setText(query.value("DESCRIPTION").toString());
        ui->comboBox_modet->setCurrentText(query.value("MODE_PAIEMENT").toString());
        ui->comboBox_typet->setCurrentText(query.value("TYPE").toString());

        // Gestion de la date de transaction
        QString dateStr = query.value("DATE_TRANSACTION").toString();
        QDate dateTransaction = QDate::fromString(dateStr, "yyyy-MM-dd");

        if (dateTransaction.isValid()) {
            ui->dateEditt->setDate(dateTransaction);
        } else {
            qDebug() << "Erreur : Format de date incorrect pour DATE_TRANSACTION";
        }
    }
}


void MainWindow::on_tabWidget_2_currentChanged()
{
    // statistique

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
        model->setQuery("select * from gs_financiere where TYPE='Depense' ");
        int number1 = model->rowCount();

        model->setQuery("select * from gs_financiere where TYPE='Revenu' ");  // Utilisez l'orthographe correcte
        int number2 = model->rowCount();



        // Calcul du total et des pourcentages
        int total = number1 + number2 ;

        QString a = QString("Depense " + QString::number((number1 * 100) / total, 'f', 2) + "%");
        QString b = QString("Revenu " + QString::number((number2 * 100) / total, 'f', 2) + "%");


        // Création de la série de données pour le graphique en camembert
        QPieSeries *series = new QPieSeries();
        series->append(a, number1);
        series->append(b, number2);


        if (number1 != 0) series->slices().at(0)->setLabelVisible();
        if (number2 != 0) series->slices().at(1)->setLabelVisible();

        // Création du graphique et configuration
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Pourcentage Par TYPE : Nombre de chaque type de transaction " + QString::number(total));
        chart->legend()->hide();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Suppression du layout précédent (s'il y en a un) et ajout du nouveau graphique
        if (ui->label_stattr->layout() != nullptr) {
            delete ui->label_stattr->layout();
        }

        QVBoxLayout *layout = new QVBoxLayout(ui->label_stattr);
        layout->addWidget(chartView);
        ui->label_stattr->setLayout(layout);
    }



