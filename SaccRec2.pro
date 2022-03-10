QT += core gui widgets

CONFIG += c++11

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    adq/bitalino.cpp \
    adq/utils.cpp \
    main.cpp \
    ui/mainwindow.cpp \
    ui/newwizard/welcomepage.cpp \
    ui/newwizard/wizard.cpp

HEADERS += \
    adq/bitalino.h \
    adq/utils.h \
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

LIBS += -lbluetooth
