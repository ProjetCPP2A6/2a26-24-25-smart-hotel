#include "arduino.h"
#include <QDebug>

Arduino::Arduino() :
    serial(new QSerialPort),
    portName(""),
    isAvailable(false)
{
    // Recherche des ports série disponibles
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.description().contains("Arduino")) { // Identifier Arduino
            portName = info.portName();
            isAvailable = true;
            break;
        }
    }
}

Arduino::~Arduino()
{
    closeArduino(); // Déconnecter proprement Arduino
    delete serial;
}

int Arduino::connectArduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   portName=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << portName;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(portName);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

int Arduino::closeArduino()
{
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Port série fermé.";
        return 0;
    }
    return -1; // Port déjà fermé
}

QString Arduino::readFromArduino()
{
    if (serial->isReadable()) {
        QByteArray data = serial->readAll();
        return QString(data);
    }
    return ""; // Aucun donnée reçue
}

int Arduino::writeToArduino(const QByteArray &data)
{
    if (serial->isWritable()) {
        serial->write(data);
        return 0; // Succès
    }
    qDebug() << "Erreur : Le port série n'est pas accessible en écriture.";
    return -1; // Échec
}

QString Arduino::getArduinoPortName() const
{
    return portName;
}

bool Arduino::getArduinoIsAvailable() const
{
    return isAvailable;
}
QSerialPort *Arduino::getserial(){
    return serial;
}
