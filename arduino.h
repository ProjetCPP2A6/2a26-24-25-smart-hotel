#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QDebug>

class Arduino
{
public:
    Arduino();  // Constructeur
    ~Arduino();  // Destructeur
    int connect_arduino();  // Connexion à l'Arduino
    int close_arduino();  // Fermeture de la connexion
    QByteArray read_from_arduino();  // Lire les données de l'Arduino
    void write_to_arduino(QByteArray d);  // Écrire des données vers l'Arduino

private:
    QSerialPort *serial;  // L'objet de communication série
    bool arduino_is_available;  // Vérifier si Arduino est disponible
    QString arduino_port_name;  // Nom du port série d'Arduino
    QByteArray data;  // Contient les données lues depuis Arduino

    static const quint16 arduino_uno_vendor_id = 9025;  // Identifiant du vendeur Arduino
    static const quint16 arduino_uno_product_id = 67;   // Identifiant du produit Arduino (pour Arduino Uno)
};

#endif // ARDUINO_H
