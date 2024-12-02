#include "arduino.h"
#include <QDebug>
#include <QSerialPortInfo>

Arduino::Arduino() : serial(nullptr), arduinoIsAvailable(false)
{
    serial = new QSerialPort();
}

int Arduino::connectArduino() {
    // Create a QSerialPort object for communication
    serial = new QSerialPort();

    // Get the list of available serial ports
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();

    // Iterate over each available serial port
    for (const QSerialPortInfo &port : serialPorts) {
        // Check if the port has the correct vendor and product IDs for the Arduino Uno
        if (port.hasVendorIdentifier() && port.hasProductIdentifier()) {
            if (port.vendorIdentifier() == arduinoUnoVendorId && port.productIdentifier() == arduinoUnoProductId) {
                // Get the port name
                arduinoPortName = port.portName();

                // Set the serial port's name
                serial->setPortName(arduinoPortName);

                // Open the serial port with read and write permissions
                if (serial->open(QIODevice::ReadWrite)) {
                    // Configure the serial port parameters (Baud rate, Data bits, Parity, etc.)
                    serial->setBaudRate(QSerialPort::Baud9600);   // Set baud rate to match Arduino's
                    serial->setDataBits(QSerialPort::Data8);       // 8 data bits
                    serial->setParity(QSerialPort::NoParity);      // No parity
                    serial->setStopBits(QSerialPort::OneStop);     // One stop bit
                    serial->setFlowControl(QSerialPort::NoFlowControl); // No flow control

                    // Mark Arduino as available
                    arduinoIsAvailable = true;
                    qDebug() << "Arduino is connected and ready on port:" << arduinoPortName;
                    return 0; // Success, Arduino connected
                } else {
                    // If the port cannot be opened, return an error code
                    qDebug() << "Failed to open serial port:" << arduinoPortName;
                    return -1; // Error, cannot open the port
                }
            }
        }
    }

    // If no Arduino Uno is found, return an error
    qDebug() << "No Arduino found!";
    return -1; // Error, Arduino not found
}

int Arduino::closeArduino()
{
    if (serial->isOpen()) {
        serial->close();
        arduinoIsAvailable = false;
        return 0;  // Successfully closed
    }
    return -1;  // Error, Arduino not open
}

void Arduino::writeToArduino(QByteArray data)
{
    if (serial->isOpen()) {
        serial->write(data);
    }
}

QByteArray Arduino::readFromArduino()
{
    if (serial->isOpen()) {
        data = serial->readAll();
        return data;
    }
    return QByteArray();
}

QSerialPort* Arduino::getSerial()
{
    return serial;
}

QString Arduino::getArduinoPortName()
{
    return arduinoPortName;
}
