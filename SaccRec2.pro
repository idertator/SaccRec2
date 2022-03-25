QT += core gui widgets svgwidgets

CONFIG += c++11

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    adq/bitalino.cpp \
    adq/utils.cpp \
    main.cpp \
    models/protocol.cpp \
    models/protocoltest.cpp \
    ui/deviceselector.cpp \
    ui/mainwindow.cpp \
    ui/newwizard/protocolpage.cpp \
    ui/newwizard/subjectpage.cpp \
    ui/newwizard/welcomepage.cpp \
    ui/newwizard/wizard.cpp \
    ui/protocols/protocoltestwidget.cpp \
    ui/protocols/protocolwidget.cpp \
    ui/settings/channelgroup.cpp \
    ui/settings/channelitem.cpp \
    ui/settings/electrodeitem.cpp \
    ui/settings/electrodespage.cpp \
    ui/settings/settings.cpp

HEADERS += \
    adq/bitalino.h \
    adq/utils.h \
    consts.h \
    models/protocol.h \
    models/protocoltest.h \
    ui/deviceselector.h \
    ui/mainwindow.h \
    ui/newwizard/protocolpage.h \
    ui/newwizard/subjectpage.h \
    ui/newwizard/welcomepage.h \
    ui/newwizard/wizard.h \
    ui/protocols/protocoltestwidget.h \
    ui/protocols/protocolwidget.h \
    ui/settings/channelgroup.h \
    ui/settings/channelitem.h \
    ui/settings/electrodeitem.h \
    ui/settings/electrodespage.h \
    ui/settings/settings.h

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
