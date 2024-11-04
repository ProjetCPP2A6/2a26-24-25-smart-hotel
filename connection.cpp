#include "connection.h"

Connection::Connection(){}

bool Connection::createconnect()
{
    bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test-bd");//inserer le nom de la source de données
    db.setUserName("taki");//inserer nom de l'utilisateur
    db.setPassword("taki");//inserer mot de passe de cet utilisateur

    if (db.open()) test=true;





    return  test;
}

void Connection::closeConnection(){db.close();}
