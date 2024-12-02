#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QByteArray>

class Arduino
{
public:
    Arduino();
    int connectArduino();
    int closeArduino();
    void writeToArduino(QByteArray data);
    QByteArray readFromArduino();
    QSerialPort* getSerial();
    QString getArduinoPortName();

private:
    QSerialPort *serial;
    static const quint16 arduinoUnoVendorId = 9025;
    static const quint16 arduinoUnoProductId = 67;
    QString arduinoPortName;
    bool arduinoIsAvailable;
    QByteArray data;
};

#endif // ARDUINO_H
