#include "Chambre.h"
#include <QSqlQuery>
#include <QMessageBox>
#include<QObject>
#include<QSqlQueryModel>
Chambre::Chambre()
{
    idchambre= 0;
    tarif=0;
    etat="";
    type="";

}

Chambre:: Chambre(int idchambre,QString etat,QString type,int tarif )
{
    this->idchambre=idchambre;
    this->etat=etat;
    this->type=type;
    this->tarif=tarif;

}

bool Chambre:: ajouter ()
{
    QSqlQuery query;

    query .prepare("insert into gs_chambre(idchambre,etat,type,tarif)"
                  " values(:idchambre, :etat, :type, :tarif)");
    query .bindValue(":idchambre", idchambre);
    query .bindValue(":etat", etat);
    query .bindValue(":type", type);
    query .bindValue(":tarif", tarif);

    return query.exec();
}

bool Chambre :: supprimer(int idchambre)
{
    QSqlQuery query;
    query .prepare("Delete from gs_chambre where idchambre= :idchambre");
    query .bindValue(":idchambre", idchambre);
    return query.exec();
}

QSqlQueryModel  * Chambre :: afficher()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("select * from gs_chambre");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("idchambre"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("etat"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("tarif"));

    return model;

}

bool Chambre::modifier(int idchambre, QString etat, QString type, int tarif)
{
    QSqlQuery query;
    query.prepare("UPDATE gs_chambre SET etat = :etat, type = :type, tarif = :tarif WHERE idchambre = :idchambre");
    query.bindValue(":etat", etat);
    query.bindValue(":type", type);
    query.bindValue(":tarif", tarif);
    query.bindValue(":idchambre", idchambre);

    return query.exec();
}



