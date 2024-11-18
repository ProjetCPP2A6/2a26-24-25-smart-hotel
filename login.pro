QT += core gui sql printsupport widgets charts multimedia

CONFIG += c++17

SOURCES += \
    connexion.cpp \
    financier.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    connexion.h \
    financier.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
