#include "financier.h"
#include<QSqlQuery>
#include<QSqlQueryModel>

#include<QString>
//#include "mainwindow.h"
#include "QSqlQuery"
#include<QMessageBox>
#include <QObject>
#include<QDate>
#include<QSqlError>

financier::financier() {}

financier::financier(int id,QDate dateTransaction, int montant, QString desc, QString type, QString modePaiement){
this->id=id;
this->dateTransaction=dateTransaction;
this->montant=montant;
this->desc=desc;
this->type=type;
this->modePaiement=modePaiement;
}
bool financier:: Add(){

    QSqlQuery query;
    query.prepare("insert into TRANSACTION1 (IDDD,MONTANT,DATE_TRANSACTION,DESCRIPTION,TYPE,MODE_PAIEMENT)"
                  "values (:IDDD ,:MONTANT , :DATE_TRANSACTION, :DESCRIPTION , :TYPE , :MODE_PAIEMENT)");
    QString res=QString::number(montant);
    QString res1=QString::number(id);
    query.bindValue(":MONTANT",res);
    query.bindValue(":IDDD",res1);
    query.bindValue(":TYPE",type);
    query.bindValue(":MODE_PAIEMENT",modePaiement);
    query.bindValue(":DESCRIPTION",desc);
    query.bindValue(":DATE_TRANSACTION",dateTransaction);
    return query.exec();


}
QSqlQueryModel *financier::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from TRANSACTION1");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDDD"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("MONTANT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("MODE_PAIEMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_TRANSACTION"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    return model;
}
bool financier::supprimer(int id)
{
    QSqlQuery query;
    QString res1=QString::number(id);
    query.prepare("delete from TRANSACTION1 where IDDD = :id");
    query.bindValue(":id",res1);
    return query.exec();
}
bool financier::Modifier_Employe(int id,QDate dateTransaction, int montant, QString desc, QString type, QString modePaiement)
{
    QSqlQuery query;

query.prepare("update TRANSACTION1 set MONTANT=:montant,MODE_PAIEMENT=:modePaiement,DATE_TRANSACTION=:dateTransaction ,TYPE=:type ,DESCRIPTION=:desc where IDDD=:id");
     query.bindValue(":id", id);
    query.bindValue(":montant", montant);
    query.bindValue(":modePaiement", modePaiement);
    query.bindValue(":dateTransaction", dateTransaction);
    query.bindValue(":type", type);
    query.bindValue(":desc", desc);
    return query.exec();
}


