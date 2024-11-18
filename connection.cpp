#include "connection.h"

Connection::Connection(){}

bool Connection::createconnect()
{
    bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("smarthotel");//inserer le nom de la source de données
    db.setUserName("projetcpp2a26");//inserer nom de l'utilisateur
    db.setPassword("mp2a26");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;
    return  test;
}

void Connection::closeConnection(){db.close();}
