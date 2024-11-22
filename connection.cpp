#include "connection.h"

Connection::Connection()
{

}


bool Connection::createconnection()
{

bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

db.setDatabaseName("CPP_Project");//inserer le nom de la source de données
db.setUserName("projetcpp2a26");//inserer nom de l'utilisateur
db.setPassword("mp2a26");//inserer mot de passe de cet utilisateur

/*db.setDatabaseName("test-bd");//inserer le nom de la source de données
db.setUserName("fadi");//inserer nom de l'utilisateur
db.setPassword("fadi");//inserer mot de passe de cet utilisateur*/

if (db.open())
test=true;





    return  test;
}

void Connection:: closeconnection()
{
    db.close();
}
