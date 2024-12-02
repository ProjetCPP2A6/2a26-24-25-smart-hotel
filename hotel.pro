QT       += core gui sql printsupport multimedia charts multimediawidgets printsupport widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connection.cpp \
    flamedetection.cpp \
    mailhandler.cpp \
    main.cpp \
    mainservice.cpp \
    service.cpp \
    taskscheduling.cpp

HEADERS += \
    arduino.h \
    connection.h \
    flamedetection.h \
    mailhandler.h \
    mainservice.h \
    service.h \
    taskscheduling.h

FORMS += \
    mainservice.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target