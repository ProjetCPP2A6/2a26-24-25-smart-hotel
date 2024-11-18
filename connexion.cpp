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
    db.setDatabaseName("CPP_Project");
    db.setUserName("projetcpp2a26");
    db.setPassword("mp2a26");
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
