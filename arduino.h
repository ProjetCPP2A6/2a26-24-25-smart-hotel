#ifndef ARDUINO_H
#define ARDUINO_H
#include<QString>
#include<QByteArray>
#include<QObject>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class Arduino
{
public:
    Arduino();
    ~Arduino();

    int connectArduino(); // Connecter Arduino
    int closeArduino();   // Déconnecter Arduino
    QString readFromArduino(); // Lire les données d'Arduino
    int writeToArduino(const QByteArray &data); // Écrire des données vers Arduino

    QString getArduinoPortName() const; // Récupérer le nom du port
    bool getArduinoIsAvailable() const; // Vérifier si Arduino est disponible
    QSerialPort* getserial();

private:
    QSerialPort *serial;        // Gestion du port série
    QString portName;           // Nom du port série
    bool isAvailable;           // Indique si Arduino est disponible

    //et des fonctions (envoi, lecture de réception,…) sur ce qu’est une voie série pour Arduino.
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;

    bool arduino_is_available;
};

#endif // ARDUINO_H
