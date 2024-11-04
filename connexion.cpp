#include "connexion.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Connexion::Connexion() {}


bool Connexion::createconnect()
{
    bool test = false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projetcpp2a26");
    db.setUserName("system");
    db.setPassword("2a26oracle");
    if (db.open()) {
        test = true;

    } else {
        qDebug() << "Database Error:" << db.lastError().text();
    }
    return test;
}

void Connexion::closeConnection()
{
    if (db.isOpen()) {
        db.close();
    }
}
