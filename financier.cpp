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
bool financier::Ajouter3()
{
    QSqlQuery query;

    // Ne pas passer l'ID ici, laissez la base de données gérer l'auto-incrément
    query.prepare("INSERT INTO gs_financiere (ID_TRANSACTION,MONTANT, DESCRIPTION, DATE_TRANSACTION, MODE_PAIEMENT, TYPE) "
                  "VALUES (:id,:montant, :desc, :date_transaction, :mode_paiement, :type)");
     query.bindValue(":id", id);
    query.bindValue(":mode_paiement", modePaiement);
    query.bindValue(":desc", desc);
    query.bindValue(":type", type);
    query.bindValue(":montant", montant);
    query.bindValue(":date_transaction", dateTransaction);
    Historique("ajout du transaction  ",id);

    return query.exec();
}




QSqlQueryModel *financier::afficher3(){
    QSqlQueryModel *model = new QSqlQueryModel();

    // Lancer la requête pour récupérer toutes les données
    model->setQuery("SELECT * FROM gs_financiere");

    // Définir les noms des colonnes dans l'affichage
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_TRANSACTION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_TRANSACTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MODE_PAIEMENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));

    return model;
}




bool financier:: supprimer3(int id)
{

    // Vérification si l' IDPAIEMENT existe dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM gs_financiere WHERE ID_TRANSACTION = :id");
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
    query.prepare("DELETE FROM gs_financiere WHERE ID_TRANSACTION = :id");
    query.bindValue(":id", id);
    Historique("Supression du transaction DE ID_TRANSACTION = ",id);

    return query.exec();

}


bool financier::modifier_paiement()
{
    QSqlQuery query;
    query.prepare("UPDATE gs_financiere SET MONTANT = :montant,TYPE = :type, MODE_PAIEMENT = :modePaiement,  DATE_TRANSACTION = :dateTransaction, DESCRIPTION = :desc WHERE ID_TRANSACTION = :id");
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
        queryString = "SELECT * FROM gs_financiere ORDER BY "
                      "CASE WHEN TYPE = 'Dépense' THEN 0 ELSE 1 END ASC, TYPE ASC";
    }
    else if (critere == "MONTANT") {
        // Trier par MONTANT du plus petit au plus grand
        queryString = "SELECT * FROM gs_financiere ORDER BY MONTANT ASC";
    }
    else {
        // Si aucun critère valide n'est sélectionné, trier par défaut
        queryString = "SELECT * FROM gs_financiere";
    }

    // Exécuter la requête
    model->setQuery(queryString);

    // Configuration des en-têtes de la table
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_TRANSACTION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_TRANSACTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MODE_PAIEMENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));

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
    QString cheminFichier = "C:/Users/user/Downloads/gestion chambre2/historique.txt";
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
    QString cheminFichier = "C:/Users/user/Downloads/gestion chambre2/historique.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(cheminFichier));
}



/*void financier::ajouterService(const QString& nomService) {
    QSqlQuery query;

    query.prepare("INSERT INTO SERVICES (NOM_SERVICE) "
                  "VALUES (:nom_service)");

    query.bindValue(":nom_service", nomService);

    if(query.exec()) {
        // Insérer une action d'historique ou un message de réussite si nécessaire
    } else {
        // Gérer les erreurs d'exécution de la requête
    }
}*/

