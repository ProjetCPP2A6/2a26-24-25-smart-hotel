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
    int montant;
    QString desc;
    QString type;
    QString modePaiement;
public:
    financier();
    financier(int id,QDate dateTransaction, int montant , QString desc , QString type , QString modePaiement  );

    //Getters
    QDate getdate(){return dateTransaction ;}
    QString getdesc(){return desc ;}
    int getmontant(){return montant ;}
      QString gettype(){return type ;}
      QString getmode(){return modePaiement ;}
    //setters

    void setdate(QDate date){dateTransaction=date;}
    void setmontant(int m){this->montant=m;}
    void setid(QString d){desc=d;}
    void settype(QString t){type=t;}
    void setmode(QString mode){modePaiement=mode;}
    //fonctionnalite
    bool Add();
    QSqlQueryModel *afficher();
    bool supprimer(int id);
    bool Modifier_Employe(int id,QDate dateTransaction, int montant, QString desc, QString type, QString modePaiement);
};

#endif // FINANCIER_H
