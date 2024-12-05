#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>
#include "reservation.h"  // Assurez-vous que cette ligne est incluse pour la classe reservation
#include <QFileDialog>


#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include "notificationwidget.h"
#include <QSystemTrayIcon>
#include <QTimer>
#include "arduino.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Rtmp.afficher());
    // Connexion à la base de données
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("hotel.db");  // Assurez-vous que le chemin est correct pour votre base de données

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données.");
        qDebug() << "Erreur de connexion:" << db.lastError();
    } else {
        // Initialiser la tableView avec les données de la base de données
        rafraichirTable();
        // Connexion à Arduino
        arduino = new Arduino();  // Assurez-vous d'initialiser l'objet Arduino
        if (arduino->connect_arduino() == 0) {
            qDebug() << "Arduino connecté!";
        } else {
            qDebug() << "Échec de la connexion à Arduino";
            QMessageBox::critical(this, "Erreur", "Échec de la connexion à Arduino.");
        }

        // Lancer la lecture périodique des données
        setupTimer();
    }

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
    delete ui;
    db.close();

}


void MainWindow::rafraichirTable()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM reservation", db);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur de requête:" << model->lastError();
    } else {
        qDebug() << "Nombre de lignes retournées:" << model->rowCount();
    }

    ui->tableView->setModel(model);  // Mettre à jour le modèle de la table
}

void MainWindow::on_comboBox_statut_activated(int index)
{
    // Implémentation pour ce slot
    qDebug() << "ComboBox Statut activated, index: " << index;
}

void MainWindow::on_comboBox_type_activated(int index)
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
    ui->comboBox_type->setCurrentIndex(0);
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
    ui->tableView->reset();  // Cette méthode réinitialise le modèle et le rafraîchit
}




    void MainWindow::oncomboBoxCritere(int index)
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
    void MainWindow::on_modifier_clicked()
    {
        int id_reservation = ui->id_reservation->text().toInt(); // Récupérer l'ID de la réservation à modifier

        // Vérifier si l'ID existe dans la base de données
        QSqlQuery query;
        query.prepare("SELECT * FROM reservation WHERE id_reservation = :id_reservation");
        query.bindValue(":id_reservation", id_reservation);
        query.exec();

        // Si l'ID existe, récupérer les données et les afficher dans les champs
        if (query.next()) {
            int id_client = query.value("id_client").toInt();
            QString type_reservation = query.value("type_reservation").toString();
            QDate date_debut = query.value("date_debut").toDate();
            QDate date_fin = query.value("date_fin").toDate();
            int nb_personnes = query.value("nb_personnes").toInt();
            QString statut = query.value("statut").toString();
            double montant = query.value("montant").toDouble();
            QString mode_paiement = query.value("mode_paiement").toString();

            // Afficher les données dans les champs
            ui->id_client->setText(QString::number(id_client));
            ui->comboBox_type->setCurrentText(type_reservation); // Assurez-vous de remplir le champ de type réservation
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
                        ui->comboBox_type->currentText(),
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
            ui->tableView->setModel(model);
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors du tri des réservations.");
        }
    }



    void MainWindow::on_rechercher_clicked()
    {
        // Récupérer le critère sélectionné dans le comboBox (id_reservation, id_client, montant)
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
            ui->tableView->setModel(model);
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
        // Récupération des données du formulaire
        int id_reservation = ui->id_reservation->text().toInt();
        int id_client = ui->id_client->text().toInt();
        QString type_reservation = ui->comboBox_type->currentText();
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
        query.prepare("SELECT COUNT(*) FROM reservation WHERE id_reservation = :id_reservation");
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
        query12.prepare("SELECT COUNT(*) FROM reservation WHERE id_client = :id_client");
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
        ui->tableView->setModel(Rtmp.afficher()); // Actualiser l'affichage des réservations
    }

    void MainWindow::on_enregistrer_clicked()
    {
        // Récupérer les nouvelles valeurs des champs
        int id_reservation = ui->id_reservation->text().toInt();
        int id_client = ui->id_client->text().toInt();
        QString type_reservation = ui->comboBox_type->currentText();
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
        queryCheck.prepare("SELECT COUNT(*) FROM reservation WHERE id_reservation = :id_reservation");
        queryCheck.bindValue(":id_reservation", id_reservation);
        queryCheck.exec();

        if (queryCheck.next() && queryCheck.value(0).toInt() == 0) {
            QMessageBox::warning(this, "Erreur", "La réservation avec cet ID n'existe pas.");
            return;
        }

        // Mettre à jour la réservation dans la base de données
        QSqlQuery query;
        query.prepare("UPDATE reservation SET id_client = :id_client, type_reservation = :type_reservation, "
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
        query.bindValue(":montant", montant);
        query.bindValue(":mode_paiement", mode_paiement);

        // Exécuter la requête
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Modification réussie !");
        } else {
            QMessageBox::warning(this, "Erreur", "La modification a échoué. Erreur : " + query.lastError().text());
        }
    }
    void MainWindow::alerte()
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
    }
  /*  void MainWindow::setupTimer() {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::updateObstacleStatus);
        timer->start(1000);  // Délai de 1 seconde pour chaque lecture
    }



    // mainwindow.cpp
    void MainWindow::updateObstacleStatus() {
        QByteArray data = arduino.read_from_arduino();  // Lire les données envoyées par Arduino
        if (!data.isEmpty()) {
            qDebug() << "Données reçues : " << data;
            QString message = QString::fromUtf8(data);  // Convertir les données en chaîne de caractères

            // Mise à jour des places disponibles en fonction du message reçu
            if (message.contains("OBSTACLE détecté")) {
                // Décrémenter le nombre de places disponibles si c'est possible
                if (placesDisponibles > 0) {
                    placesDisponibles--;  // Décrémenter le nombre de places disponibles
                }

                // Si le nombre de places devient 0, afficher "Aucune place disponible"
                if (placesDisponibles == 0) {
                    ui->label1->setText("Aucune place disponible.");
                } else {
                    // Si des places sont encore disponibles, afficher le nombre de places restantes
                    ui->label1->setText(QString::number(placesDisponibles) + " place(s) disponible(s).");
                }
            } else if (message.contains("Aucun obstacle")) {
                // Si aucun obstacle n'est détecté (pas de changement dans les places disponibles)
                // Afficher "Aucune voiture détectée" et ne pas changer les places
                ui->label1->setText("Aucune voiture détectée.");
            }
        }
    }
    void MainWindow::readFromArduino() {
        QByteArray data = arduino.read_from_arduino();  // Lire les données envoyées par Arduino

        if (!data.isEmpty()) {
            qDebug() << "Données reçues : " << data;
            QString message = QString::fromUtf8(data);  // Convertir les données en chaîne de caractères

            // Mise à jour du texte du label et gestion des places disponibles
            if (message.contains("OBSTACLE détecté")) {
                // Décrémenter le nombre de places disponibles si c'est possible
                if (placesDisponibles > 0) {
                    placesDisponibles--;  // Décrémenter le nombre de places disponibles
                }

                // Si le nombre de places devient 0, afficher "Aucune place disponible"
                if (placesDisponibles == 0) {
                    ui->label1->setText("Aucune place disponible.");
                } else {
                    // Si des places sont encore disponibles, afficher le nombre de places restantes
                    ui->label1->setText(QString::number(placesDisponibles) + " place(s) disponible(s).");
                }
            } else if (message.contains("Aucun obstacle")) {
                // Si aucun obstacle n'est détecté (pas de changement dans les places disponibles)
                // Afficher "Aucune voiture détectée" et ne pas changer les places
                ui->label1->setText("Aucune voiture détectée.");
            }
        }
    }*/
    void MainWindow::on_pushButton_statistiques_clicked()
    {


        // Création du modèle de requêtes SQL
        QSqlQueryModel *model = new QSqlQueryModel();

        // Requêtes pour chaque type de réservation
        model->setQuery("SELECT * FROM reservation WHERE TYPE_RESERVATION='Chambre'");
        int number1 = model->rowCount();

        model->setQuery("SELECT * FROM reservation WHERE TYPE_RESERVATION='Restaurant'");
        int number2 = model->rowCount();

        model->setQuery("SELECT * FROM reservation WHERE TYPE_RESERVATION='Parking'");
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





    void MainWindow::setupTimer() {
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
    }



