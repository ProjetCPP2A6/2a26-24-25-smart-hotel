#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiel.h"
#include <QMessageBox>
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*void MainWindow::on_pushButtonAjout_clicked() {
    // Retrieving the values from the input fields

    int id = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QString  = ui->type->text();
    int quantite = ui->quantite->text().toInt();
    QString etat = ui->etat->text().toFloat();



    // Create an Employee instance
    Employee emp(cin, name, prename, birthDate, salary, username, password, department, position);

    // Call the ajouter() method to add the employee and get the result
    bool test = emp.ajouter();

    // If ajout (add) is successful
    if (test) {
        // Refresh the table view
        ui->tableView->setModel(emp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué \n"
                                             "Click Cancel to exit"),
                                 QMessageBox::Cancel);
    } else {
        // If ajout (add) fails
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit"),
                              QMessageBox::Cancel);
    }
}*/



void MainWindow::on_ajouterMateriel_clicked()
{
    int id = ui->id->text().toInt();
    QString idd = ui->id->text();
    QString nom = ui->nom->text();
    QString type = ui->type->text();
    QDate Date = ui->dateEdit->date();
    int quantite = ui->quantite_2->text().toInt();
    QString quantitee = ui->quantite_2->text();
    QString etat = ui->etat->text();

    Materiel m(id,nom,type,quantite,etat,Date);
    if(nom=="" || type==""  || etat=="" || quantitee=="" || idd=="" )
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("veuillez remplir tous les champs"),
                              QMessageBox::Cancel);
    }
    else{
        m.ajouterMateriel();
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué \n"
                                             "Click Cancel to exit"),
                                 QMessageBox::Cancel);
    }


}

void MainWindow::on_pushButton_4_clicked()
{
    Materiel m;
    ui->tableView_2->setModel(m.afficher());
}

void MainWindow::on_pushButton_2_clicked()
{
    int id = ui->id->text().toInt();
    Materiel m;
    m.supprimer(id);
}

void MainWindow::on_pushButton_3_clicked()
{
    int id = ui->id->text().toInt();
    QString idd = ui->id->text();
    QString nom = ui->nom->text();
    QString type = ui->type->text();
    Materiel m(id,nom,type);

    if(nom=="" || type=="" || idd=="" )
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("veuillez remplir tous les champs"),
                              QMessageBox::Cancel);
    }
    else{
        m.modifier();
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("modification effectué \n"
                                             "Click Cancel to exit"),
                                 QMessageBox::Cancel);
    }

}

void MainWindow::on_pushButton_5_clicked()
{
   QString option =  ui->tri->currentText();
   if(option=="quantite")
   {
       Materiel m;
       ui->tableView_2->setModel(m.tri1());
   }
   else
   {
       Materiel m;
       ui->tableView_2->setModel(m.tri2());
   }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString id = ui->etat_2->text();
    Materiel m;
    ui->tableView_2->setModel(m.rechercher(id));
}

void MainWindow::on_pushButton_7_clicked()
{
    QSqlQuery query;
    query.exec("SELECT ETAT, COUNT(*) FROM MATERIELS GROUP BY ETAT");

    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    while (query.next()) {
        QString ETAT = query.value(0).toString();
        int count = query.value(1).toInt();
        QtCharts::QPieSlice *slice = new QtCharts::QPieSlice(ETAT, count);
        series->append(slice);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistics based on MATERIELS ETAT");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->tableView);
    chartView->resize(ui->tableView->size());
    chartView->show();
}

void MainWindow::on_pushButton_clicked()
{
    QPdfWriter pdf("C:/Users/HP/OneDrive/Bureau/materiels/materiel.pdf");

           QPainter painter(&pdf);
           int i = 4100;

                  QColor dateColor(0x4a5bcf);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(7700,250,cd.toString("Ariana, El Ghazela"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,2700,"Liste des materiels");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));
                              painter.drawText(300,3600,"id_materiel");
                              painter.drawText(2000,3600,"nom");
                              painter.drawText(3000,3600,"type");
                              painter.drawText(4000,3600,"quantite");
                              painter.drawText(5000,3600,"etat");
                              painter.drawText(7000,3600,"date_acquisition");
                              painter.drawText(9000,3600,"id_employe");
                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from MATERIELS");
                  query.exec();
                  int y=4300;
                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);
                      y+=500;
                      painter.drawText(300,i,query.value(0).toString());
                          painter.drawText(2000,i,query.value(1).toString());
                          painter.drawText(3000,i,query.value(2).toString());
                          painter.drawText(4000,i,query.value(3).toString());
                          painter.drawText(5000,i,query.value(4).toString());
                          painter.drawText(7000,i,query.value(5).toString());
                          painter.drawText(9000,i,query.value(6).toString());
                     i = i + 500;
                  }

                  int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré.\nVous voulez l'affichez ?", QMessageBox::Yes |  QMessageBox::No);
                  if (reponse == QMessageBox::Yes)
                  {
                      QDesktopServices::openUrl( QUrl::fromLocalFile("C:/Users/HP/OneDrive/Bureau/materiels/materiel.pdf"));
                      painter.end();
                  }
                  else
                  {
                      painter.end();
                  }
}

void MainWindow::on_pushButton_8_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Choose Image"), QDir::currentPath(), tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (imagePath.isEmpty()) {
               return;
           }

           // Read the image file
           QFile file(imagePath);
           if (!file.open(QIODevice::ReadOnly)) {
               qDebug() << "Failed to open image file:" << imagePath;
               return;
           }
    QByteArray imageData = file.readAll();
    QString ID = ui->id->text();
    if (!insertImageIntoDatabase(imageData,ID)) {
               qDebug() << "Failed to insert image into database.";
               return;
           }

           qDebug() << "Image inserted into database successfully.";
}
bool MainWindow::insertImageIntoDatabase(const QByteArray& imageData,QString ID) {


       // Prepare SQL query
       QSqlQuery query;
       query.prepare("UPDATE materiels SET image = :imageData WHERE ID_materiel = :id");
       query.bindValue(":imageData", imageData);
       query.bindValue(":id", ID);
       // Execute the query
       if (!query.exec()) {
           qDebug() << "Failed to insert image into database:";
           return false;
       }

       return true;
   }

void MainWindow::on_pushButton_9_clicked()
{
    QString ID = ui->id->text();



       // Prepare SQL query to retrieve image data based on ID
       QSqlQuery query;
       query.prepare("SELECT image FROM materiels WHERE ID_materiel = :id");
       query.bindValue(":id", ID);

       // Execute the query
       if (!query.exec()) {
           qDebug() << "Failed to retrieve image data from database:" ;
           return;
       }

       // Check if a record was found
       if (!query.next()) {
           qDebug() << "No image found for the given ID.";
           return;
       }

       // Retrieve image data from the query result
       QByteArray imageData = query.value("image").toByteArray();

       // Convert image data to QPixmap and display
       QPixmap pixmap;
       pixmap.loadFromData(imageData);

       // Assuming you have a QLabel named imageLabel where you want to display the image
       ui->label->setPixmap(pixmap);
       ui->label->setScaledContents(true);
       ui->quantite->setCurrentIndex(1);
}

void MainWindow::on_pushButton_10_clicked()
{
    QSqlQuery query;
       query.prepare("SELECT SUM(cout_rep) FROM materiels where etat='non fonctionnel'");

       // Execute the query
       if (query.exec()) {
           if (query.next()) {
               double sum = query.value(0).toDouble();
               // Display the result (for example, in a message box)
               QMessageBox::information(this, "Sum of cout_rep", "The sum of cout_rep is: " + QString::number(sum));
           }
       } else {
           // Handle query execution failure
           QMessageBox::critical(this, "Error", "Failed to execute query: ");
       }
}

void MainWindow::on_ajouterMateriel_2_clicked()
{
    QString cout = ui->etat_3->text();
    QString id = ui->id->text();
    QSqlQuery query;
       query.prepare("UPDATE MATERIELS SET COUT_REP=:cout where id_materiel=:id");
       query.bindValue(":id",id);
       query.bindValue(":cout",cout);
       // Execute the query
       if (query.exec())
       {
            QMessageBox::information(this, "done", "cout added ");
       }
       else{
            QMessageBox::information(this, "error", "error ");
       }

}
