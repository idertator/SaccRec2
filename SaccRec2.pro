QT += core gui widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    ui/mainwindow.cpp \
    ui/newwizard/welcomepage.cpp \
    ui/newwizard/wizard.cpp

HEADERS += \
    ui/mainwindow.h \
    ui/newwizard/welcomepage.h \
    ui/newwizard/wizard.h

TRANSLATIONS += \
    SaccRec2_es_ES.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res/resources.qrc