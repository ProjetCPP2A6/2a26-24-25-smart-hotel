#ifndef FINANCIER_H
#define FINANCIER_H

#include <QMainWindow>
#include <QDate>
#include <QSqlQuery>
#include<QSqlQueryModel>


class financier
{

private:
    int id;
    QDate dateTransaction;
    QString montant;
    QString desc;
    QString type;
    QString modePaiement;
public:
    financier();
    financier(int id,QDate dateTransaction, QString montant , QString desc , QString type , QString modePaiement  );

    void setId(int id); // Déclaration de la méthode setId
    void setMontant(const QString& montant); // Déclaration de la méthode setMontant
    //Getters
    QDate getdate(){return dateTransaction ;}
    QString getdesc(){return desc ;}
    QString getmontant(){return montant ;}
    QString gettype(){return type ;}
    QString getmode(){return modePaiement ;}
    //setters

    void setdate(QDate date){dateTransaction=date;}
    void setmontant(QString m){this->montant=m;}
    void setid(QString d){desc=d;}
    void settype(QString t){type=t;}
    void setmode(QString mode){modePaiement=mode;}
    //fonctionnalite
    bool Add();
    QSqlQueryModel *afficher();
    bool supprimer(int id);
    bool modifier_paiement();
    QSqlQueryModel* tri_paiement(const QString& critere);
    bool PDF(const QString& fileName, QSqlQueryModel* model);
    bool recherche(int id, const QString& modePaiement, const QString& type, QSqlQueryModel*& model);
    void stat_paiement(QSqlQueryModel* model, QWidget* chartView);
    void Historique(const QString &action,int IDD);
    void History_recherche(const QString &action,int id);
    void afficherHistorique();
    void ouvrirHistorique();
    void processIdPaiement();

    void ajouterService(const QString& nomService) ;
};

#endif // FINANCIER_H
