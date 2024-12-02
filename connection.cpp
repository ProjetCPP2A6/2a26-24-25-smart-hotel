#include "connection.h"

Connection::Connection() {}

bool Connection::createconnect() {
    bool test = false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test-bd");  // Insert the name of your data source
    db.setUserName("taki");  // Insert the username
    db.setPassword("taki");  // Insert the password for the user

    if (db.open()) test = true;

    return test;
}

