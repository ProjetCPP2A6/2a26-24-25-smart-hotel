QT += core gui sql printsupport widgets charts multimedia serialport


CONFIG += c++17

SOURCES += \
    arduino.cpp \
    connexion.cpp \
    financier.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    arduino.h \
    connexion.h \
    financier.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
