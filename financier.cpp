#include "financier.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QString>
#include <QDate>
#include <QDateEdit>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QPrinter>
#include <QTextDocument>
#include <QSizeF>
#include <QPageSize>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>

financier::financier() {
    id = 0;
    montant = "";
    dateTransaction = QDate::currentDate();
    desc = "";
    type = "";
    modePaiement = "" ;
}
void financier::setId(int id) {
    this->id = id;
}

void financier::setMontant(const QString& montant) {
    this->montant = montant;
}
financier::financier(int id,QDate dateTransaction, QString montant, QString desc, QString type, QString modePaiement){
    this->id=id;
    this->dateTransaction=dateTransaction;
    this->montant=montant;
    this->desc=desc;
    this->type=type;
    this->modePaiement=modePaiement;
}
bool financier::Add()
{
    QSqlQuery query;

    // Ne pas passer l'ID ici, laissez la base de données gérer l'auto-incrément
    query.prepare("INSERT INTO TRANSACTIONS (MODE_PAIEMENT, DESCRIPTION, TYPE, MONTANT, DATE_TRANSACTION) "
                  "VALUES (:mode_paiement, :desc, :type, :montant, :date_transaction)");

    query.bindValue(":mode_paiement", modePaiement);
    query.bindValue(":desc", desc);
    query.bindValue(":type", type);
    query.bindValue(":montant", montant);
    query.bindValue(":date_transaction", dateTransaction);
    Historique("ajout du transaction  ",id);

    return query.exec();
}




QSqlQueryModel *financier::afficher(){
    QSqlQueryModel *model = new QSqlQueryModel();

    // Lancer la requête pour récupérer toutes les données
    model->setQuery("SELECT * FROM TRANSACTIONS");

    // Définir les noms des colonnes dans l'affichage
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_TRANSACTION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_TRANSACTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MODE_PAIEMENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));

    return model;
}




bool financier:: supprimer(int id)
{

    // Vérification si l' IDPAIEMENT existe dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM TRANSACTIONS WHERE ID_TRANSACTION = :id");
    checkQuery.bindValue(":id", id);
    if (!checkQuery.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la vérification du ID.");
        return false;
    }
    checkQuery.next();
    int count = checkQuery.value(0).toInt();
    if (count == 0) {
        QMessageBox::information(nullptr, "Information", "L' ID spécifié n'existe pas dans la base de données.");
        return false;
    }


    // Requête de suppression
    QSqlQuery query;
    query.prepare("DELETE FROM TRANSACTIONS WHERE ID_TRANSACTION = :id");
    query.bindValue(":id", id);
    Historique("Supression du transaction DE ID_TRANSACTION = ",id);

    return query.exec();

}


bool financier::modifier_paiement()
{
    QSqlQuery query;
    query.prepare("UPDATE TRANSACTIONS SET MONTANT = :montant,TYPE = :type, MODE_PAIEMENT = :modePaiement,  DATE_TRANSACTION = :dateTransaction, DESCRIPTION = :desc WHERE ID_TRANSACTION = :id");
    query.bindValue(":id", id);
    query.bindValue(":montant", montant);
    query.bindValue(":modePaiement", modePaiement);
    query.bindValue(":dateTransaction", dateTransaction);
    query.bindValue(":type", type);
    query.bindValue(":desc", desc);
    Historique("Modification du transaction  ",id);

    return query.exec();
}
QSqlQueryModel* financier::tri_paiement(const QString& critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryString;

    // Vérifier le critère choisi
    if (critere == "TYPE") {
        // Trier par TYPE, en mettant 'Dépenses' avant 'Revenus'
        // Assurez-vous que le champ 'TYPE' contient les valeurs exactes "Dépense" et "Revenu"
        queryString = "SELECT * FROM TRANSACTIONS ORDER BY "
                      "CASE WHEN TYPE = 'Dépense' THEN 0 ELSE 1 END ASC, TYPE ASC";
    }
    else if (critere == "MONTANT") {
        // Trier par MONTANT du plus petit au plus grand
        queryString = "SELECT * FROM TRANSACTIONS ORDER BY MONTANT ASC";
    }
    else {
        // Si aucun critère valide n'est sélectionné, trier par défaut
        queryString = "SELECT * FROM TRANSACTIONS";
    }

    // Exécuter la requête
    model->setQuery(queryString);

    // Configuration des en-têtes de la table
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_TRANSACTION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_TRANSACTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MODE_PAIEMENT"));

    return model;
}







bool financier::PDF(const QString& fileName, QSqlQueryModel* model)
{
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    printer.setPageSize(QPageSize::A3);

    printer.setOutputFileName(fileName);

    QPainter painter(&printer);
    if (!painter.isActive()) {
        QMessageBox::warning(nullptr, "Erreur", "Impossible de dessiner sur l'imprimante.");
        return false;
    }

    QTextDocument doc;

    // Définir le contenu HTML du PDF
    QString html = "<html><head><style>"
                   "table { border-collapse: collapse; width: 100%; }"
                   "th, td { border: 1px solid #dddddd; text-align: left; padding: 8px; font-size: 12px; }"
                   "th { background-color: #f2f2f2; }"
                   "</style></head><body>"
                   "<h1>Les Transactions</h1>"  // Titre de la page
                   "<table>";

    // Ajouter les en-têtes
    html += "<tr>";
    for (int col = 0; col < model->columnCount(); ++col) {
        html += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";

    // Afficher seulement la première ligne du modèle
    int row = 0;
    if (model->rowCount() > 0) {
        html += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            html += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
        }
        html += "</tr>";
    }

    html += "</table></body></html>";

    // Créer le document à partir du HTML
    doc.setHtml(html);
    doc.drawContents(&painter);

    return true;
}


bool financier::recherche(int id, const QString& modePaiement, const QString& type, QSqlQueryModel*& model)
{
    if (id < 0 && modePaiement.isEmpty() && type.isEmpty()) {
        QMessageBox::information(nullptr, "Information", "Veuillez fournir au moins un critère de recherche.");
        return false;
    }

    QSqlQuery query;
    QString queryStr = "SELECT * FROM TRANSACTIONS WHERE 1=1";

    if (id > 0) {
        queryStr += " AND ID_TRANSACTION = :id";
    }
    if (!modePaiement.isEmpty()) {
        queryStr += " AND LOWER(MODE_PAIEMENT) = LOWER(:modePaiement)";
    }
    if (!type.isEmpty()) {
        queryStr += " AND LOWER(TYPE) = LOWER(:type)";
    }

    qDebug() << "Requête générée : " << queryStr;

    query.prepare(queryStr);

    // Bind des valeurs conditionnellement
    if (id > 0) {
        query.bindValue(":id", id);
    }
    if (!modePaiement.isEmpty()) {
        query.bindValue(":modePaiement", modePaiement);
    }
    if (!type.isEmpty()) {
        query.bindValue(":type", type);
    }

    if (!query.exec()) {
      //  qDebug() << "Erreur SQL : " << query.lastError().text();
        //QMessageBox::critical(nullptr, "Erreur", "Erreur SQL : " + query.lastError().text());
        return false;
    }

    model = new QSqlQueryModel();
    model->setQuery(query);

    if (model->rowCount() == 0) {
        QMessageBox::information(nullptr, "Information", "Aucune transaction trouvée avec les critères spécifiés.");
        delete model; // Éviter les fuites de mémoire
        model = nullptr;
        return false;
    }

    return true;
}


void financier::stat_paiement(QSqlQueryModel* model, QWidget* chartView) {
    QPieSeries *series = new QPieSeries();

    int countEspece = 0;
    int countVirement = 0;

    // Comptage des différents types de paiement
    for (int row = 0; row < model->rowCount(); ++row) {
        QString modePaiement = model->data(model->index(row, 4)).toString();

        if (modePaiement.toLower() == "espece") {
            countEspece++;
        } else if (modePaiement.toLower() == "virement") {
            countVirement++;
        }
    }

    int totalCount = countEspece + countVirement;
    qreal percentEspece = (static_cast<qreal>(countEspece) / totalCount) * 100.0;
    qreal percentVirement = (static_cast<qreal>(countVirement) / totalCount) * 100.0;

    series->append("Espece (" + QString::number(percentEspece, 'f', 1) + "%)", percentEspece)->setBrush(QBrush(Qt::blue));
    series->append("Virement (" + QString::number(percentVirement, 'f', 1) + "%)", percentVirement)->setBrush(QBrush(Qt::green));

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelOutside);

    // Appliquer une police pour les labels
    QFont labelFont;
    labelFont.setBold(true);
    labelFont.setPointSize(10);

    // Appliquer la police à toutes les tranches
    for (auto slice : series->slices()) {
        slice->setLabelFont(labelFont);
        slice->setLabelColor(Qt::darkGray);
        // Optionnel : on peut aussi ajouter un effet statique pour les tranches
        // slice->setExploded(true);  // Exploser une tranche si nécessaire
    }

    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des paiements par type");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setDropShadowEnabled(true);

    // Créer un QChartView pour afficher le graphique
    QChartView *chartViewWidget = new QChartView(chart);
    chartViewWidget->setRenderHint(QPainter::Antialiasing);

    // Vérifier si un layout existe déjà
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(chartView->layout());
    if (!layout) {
        layout = new QVBoxLayout(chartView);  // Si pas de layout, créer un nouveau
        chartView->setLayout(layout);
    }

    // Ajouter le QChartView au layout
    layout->addWidget(chartViewWidget);
}




void financier::History_recherche(const QString &action,int id) {
    // Ouvrir le fichier en écriture
    QString cheminFichier ="C:/Users/eleuc/OneDrive/Bureau/lundi 2/lundi 2/login/historique.txt";
    QFile file(cheminFichier);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique.";
        return;
    }

    // Créer un flux texte pour écrire dans le fichier
    QTextStream out(&file);

    // Obtenir la date et l'heure actuelles
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Écrire l'action dans le fichier historique avec la date et l'heure
    out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " - " << action;
    if (id < 0) {
        out << " " << id;
    }
    out << "\n";

    // Fermer le fichier
    file.close();
}




void financier::Historique(const QString &action,int IDD)
{
    // Ouvrir le fichier en écriture
    QString cheminFichier = "C:/Users/eleuc/OneDrive/Bureau/lundi 2/lundi 2/login/historique.txt";
    QFile file(cheminFichier);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique.";
        return;

    }

    // Créer un flux texte pour écrire dans le fichier
    QTextStream out(&file);

    // Obtenir la date et l'heure actuelles
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Écrire l'action dans le fichier historique avec la date et l'heure
    out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " - " << action;
    if (IDD != 0) {
        out << " de ID_TRANSACTION " << IDD;
    }
    out << "\n";

    // Fermer le fichier
    file.close();
}



void financier::ouvrirHistorique()
{
    QString cheminFichier = "C:/Users/eleuc/OneDrive/Bureau/lundi 2/lundi 2/login/historique.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(cheminFichier));
}



void financier::ajouterService(const QString& nomService) {
    QSqlQuery query;

    query.prepare("INSERT INTO SERVICES (NOM_SERVICE) "
                  "VALUES (:nom_service)");

    query.bindValue(":nom_service", nomService);

    if(query.exec()) {
        // Insérer une action d'historique ou un message de réussite si nécessaire
    } else {
        // Gérer les erreurs d'exécution de la requête
    }
}

