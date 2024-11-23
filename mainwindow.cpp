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


#include <QtSql/QSqlQueryModel>       // Pour utiliser QSqlQueryModel pour les requêtes SQL
#include <QtCharts/QChart>            // Pour la création du graphique
#include <QtCharts/QChartView>        // Pour afficher le graphique
#include <QtCharts/QPieSeries>        // Pour la série de graphique en camembert (pie chart)
#include <QtCharts/QPieSlice>         // Pour les morceaux individuels du graphique en camembert
#include <QMediaPlayer>               // Pour lire un son lors du clic
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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_ID->setValidator(new QIntValidator(0,9999,this));
    //ui->lineEdit_supp->setValidator(new QIntValidator(0,9999,this));

     connect(ui->lineEdit_ID, &QLineEdit::editingFinished, this, &MainWindow::on_lineEdit_ID_editingFinished);
    connect(ui->pushButton_tri, &QPushButton::clicked, this, &MainWindow::on_pushButton_tri_clicked);


    ui->comboBox_trier->addItem("etat");
    ui->comboBox_trier->addItem("type");
    ui->comboBox_trier->addItem("tarif");

    ui->tableView->setModel(CHtmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    /*int idchambre=ui->lineEdit_ID->text().toInt();
    QString etat =ui->comboBox_etat->currentText();
    QString type =ui->comboBox_type->currentText();
    int tarif=ui->lineEdit_T->text().toInt();

    Chambre CH (idchambre,etat,type,tarif);
    bool test= CH.ajouter();
    if(test)
    {
        ui->tableView->setModel(CHtmp.afficher());
        QMessageBox :: information(nullptr,QObject::tr("ok"),
                                  QObject::tr("Ajout effectue/n"
                                              "click cancel to exit."),
                                  QMessageBox :: Cancel);
    //clearChambreFields();
    }
    else
    {
        QMessageBox :: critical(nullptr,QObject::tr("Not ok"),
                               QObject::tr("Ajout non effectue/n" "click cancel to exit."),
                               QMessageBox :: Cancel);
    }*/

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


    /*int idchambre = ui->lineEdit_supp->text().toInt();

    // Vérifiez si l'ID de la chambre existe avant de supprimer
    QSqlQuery query;  //crée un objet de requête SQL
    query.prepare("SELECT COUNT(*) FROM gs_chambre WHERE idchambre = :idchambre"); //renvoie le nombre de lignes dans la tabl
    query.bindValue(":idchambre", idchambre);
    query.exec();

    if (query.next() && query.value(0).toInt() > 0) {
        // L'ID existe, on peut procéder à la suppression
        bool test = CHtmp.supprimer(idchambre);
        if (test) {
            ui->tableView->setModel(CHtmp.afficher());
            QMessageBox::information(this, QObject::tr("ok"),
                                     QObject::tr("Suppression effectuée.\n"
                                                 "Cliquez sur Annuler pour quitter."),
                                     QMessageBox::Cancel);
            // Effacer le champ après suppression
            ui->lineEdit_supp->clear();
        } else {
            QMessageBox::critical(this, QObject::tr("Not ok"),
                                  QObject::tr("Suppression non effectuée.\n"
                                              "Cliquez sur Annuler pour quitter."),
                                  QMessageBox::Cancel);
        }
    } else {
        // L'ID n'existe pas
        QMessageBox::warning(this, QObject::tr("Erreur"),
                             QObject::tr("L'ID spécifié n'existe pas.\n"
                                         "Veuillez vérifier l'ID et réessayer."),
                             QMessageBox::Cancel);
    }*/

    QString idChambre = ui->lineEdit_Rech->text();

    // Vérifiez si l'ID est vide
    if (idChambre.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID de chambre.");
        return; // Ne rien faire si le champ est vide
    }

    // Vérifiez si l'ID de la chambre existe avant de supprimer
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM gs_chambre WHERE idchambre = :idchambre");
    query.bindValue(":idchambre", idChambre);
    query.exec();

    if (query.next() && query.value(0).toInt() > 0) {
        // L'ID existe, on peut procéder à la suppression
        bool test = CHtmp.supprimer(idChambre.toInt()); // Assurez-vous que supprimer() accepte un int si nécessaire
        if (test) {
            ui->tableView->setModel(CHtmp.afficher());  // Actualiser l'affichage après suppression
            QMessageBox::information(this, "Ok", "Suppression effectuée.");
            ui->lineEdit_Rech->clear();  // Effacer le champ après suppression
        } else {
            QMessageBox::critical(this, "Not Ok", "Suppression non effectuée.");
        }
    } else {
        // L'ID n'existe pas
        QMessageBox::warning(this, "Erreur", "L'ID spécifié n'existe pas.\nVeuillez vérifier l'ID et réessayer.");
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
    ui->comboBox_etat->setCurrentIndex(-1); // Réinitialiser le comboBox
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
    /*QString idChambre = ui->lineEdit_Rech->text();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Prépare la requête pour rechercher la chambre par ID
    query.prepare("SELECT * FROM gs_chambre WHERE idchambre = :idchambre");
    query.bindValue(":idchambre", idChambre);

    // Exécute la requête
    if (query.exec()) {
         model->setQuery(std::move(query));
        ui->tableView->setModel(model);

        // Vérifie si des résultats ont été trouvés
        if (model->rowCount() > 0) {
            // Colorie la ligne en vert si l'ID est trouvé
            for (int row = 0; row < model->rowCount(); ++row) {
                if (model->data(model->index(row, 0)).toString() == idChambre) {
                    // Applique la couleur verte à la ligne
                    for (int col = 0; col < model->columnCount(); ++col) {
                        ui->tableView->model()->setData(
                            model->index(row, col), QBrush(Qt::green), Qt::BackgroundRole
                            );
                    }
                    break;
                }
            }
        } else {
            // Affiche un message si aucun résultat n'est trouvé
            QMessageBox::information(this, "Recherche", "L'ID " + idChambre + " n'existe pas.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la recherche : " + query.lastError().text());
    }
    ui->lineEdit_Rech->clear();*/
    if(ui->comboBox_trier_2->currentText()=="idchambre")
    {
    QString idChambre = ui->lineEdit_Rech->text();

    // Vérifiez si l'ID est vide
    if (idChambre.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID de chambre.");
        return; // Ne rien faire si le champ est vide
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Prépare la requête pour rechercher la chambre par ID
    query.prepare("SELECT * FROM gs_chambre WHERE idchambre = :idchambre");
    query.bindValue(":idchambre", idChambre);

    // Exécute la requête
    if (query.exec()) {
        model->setQuery(std::move(query));
        ui->tableView->setModel(model);

        // Vérifie si des résultats ont été trouvés
        if (model->rowCount() > 0) {
            // Colorie la ligne en vert si l'ID est trouvé
            for (int row = 0; row < model->rowCount(); ++row) {
                if (model->data(model->index(row, 0)).toString() == idChambre) {
                    // Applique la couleur verte à la ligne
                    for (int col = 0; col < model->columnCount(); ++col) {
                        ui->tableView->model()->setData(
                            model->index(row, col), QBrush(Qt::green), Qt::BackgroundRole
                            );
                    }
                    break;
                }
            }
        } else {
            // Affiche un message si aucun résultat n'est trouvé
            QMessageBox::information(this, "Recherche", "L'ID " + idChambre + " n'existe pas.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la recherche : " + query.lastError().text());
    }
    }

    else{
        QString idChambre = ui->lineEdit_Rech->text();

        // Vérifiez si l'ID est vide
        if (idChambre.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID de chambre.");
            return; // Ne rien faire si le champ est vide
        }

        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;

        // Prépare la requête pour rechercher la chambre par ID
        query.prepare("SELECT * FROM gs_chambre WHERE tarif = :idchambre");
        query.bindValue(":idchambre", idChambre);

        // Exécute la requête
        if (query.exec()) {
            model->setQuery(std::move(query));
            ui->tableView->setModel(model);

            // Vérifie si des résultats ont été trouvés
            if (model->rowCount() > 0) {
                // Colorie la ligne en vert si l'ID est trouvé
                for (int row = 0; row < model->rowCount(); ++row) {
                    if (model->data(model->index(row, 0)).toString() == idChambre) {
                        // Applique la couleur verte à la ligne
                        for (int col = 0; col < model->columnCount(); ++col) {
                            ui->tableView->model()->setData(
                                model->index(row, col), QBrush(Qt::green), Qt::BackgroundRole
                                );
                        }
                        break;
                    }
                }
            } else {
                // Affiche un message si aucun résultat n'est trouvé
                QMessageBox::information(this, "Recherche", "tarif " + idChambre + " n'existe pas.");
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la recherche : " + query.lastError().text());
        }
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

}






void MainWindow::on_pushButton_exporter_2_clicked()
{
    int idchambre=ui->lineEdit_ID->text().toInt();
    QString etat =ui->comboBox_etat->currentText();
    QString type =ui->comboBox_type->currentText();
    int tarif=ui->lineEdit_T->text().toInt();
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



}


void MainWindow::createPDF(int idchambre, const QString& etat, const QString& type, int tarif, const QString& id, const QString& date_debut, const QString& date_fin) {
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
    painter.drawText(50, y, "Tarif: " + QString::number(tarif));
    y += lineHeight;

    // Set text color to green for "Reservation Details"
    painter.setPen(Qt::green);
    painter.drawText(50, y, "Reservation Details:");
    y += lineHeight;

    // Restore text color to default (black) for the rest of the content
    painter.setPen(Qt::black);
    /*painter.drawText(50, y, "ID Reservation: " + id);
    y += lineHeight;*/
    painter.drawText(50, y, "Date Debut: " + date_debut);
    y += lineHeight;
    painter.drawText(50, y, "Date Fin: " + date_fin);
    y += lineHeight;

    // Finish and save
    painter.end();

    qDebug() << "PDF saved successfully at: " << filePath;
}
