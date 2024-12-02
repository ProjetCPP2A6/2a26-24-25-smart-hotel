#include "Arduino.h"

Arduino::Arduino() {
    serial = new QSerialPort();
    arduino_is_available = false;
}

Arduino::~Arduino() {
    if (serial != nullptr) {
        delete serial;
    }
}

int Arduino::connect_arduino() {
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_product_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                break;
            }
        }
    }

    if (arduino_is_available) {
        qDebug() << "Port série trouvé : " << arduino_port_name;
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "Port série ouvert avec succès";
            return 0;
        } else {
            qDebug() << "Impossible d'ouvrir le port série";
        }
    }
    return 1;
}

int Arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Port série fermé";
        return 0;
    }
    qDebug() << "Le port série était déjà fermé";
    return 1;
}

QByteArray Arduino::read_from_arduino() {
    if (serial->isReadable()) {
        return serial->readAll();
    }
    return QByteArray();
}

void Arduino::write_to_arduino(QByteArray d) {
    if (serial->isWritable()) {
        serial->write(d);
        qDebug() << "Données envoyées à Arduino : " << d;
    } else {
        qDebug() << "Impossible d'écrire dans le port série";
    }
}
