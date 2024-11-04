#ifndef CONNEXION_H
#define CONNEXION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connexion {
public:
    Connexion();
    bool createconnect();
    void closeConnection();

private:
    QSqlDatabase db;
};


#endif // CONNEXION_H
