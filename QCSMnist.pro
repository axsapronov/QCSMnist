#-------------------------------------------------
#
# Project created by QtCreator 2012-07-10T00:08:18
#
#-------------------------------------------------

QT       += core gui

TARGET = QCSMnist
TEMPLATE = app


PROJECTNAME = QCSMnist
DESTDIR     = build/bin
OBJECTS_DIR = build/obj
MOC_DIR     = build/moc
RCC_DIR     = build/rc
UI_DIR      = build/ui

INCLUDEPATH = \
    src \
    src/dialogs/about \
    src/main \
    src/other \
    src/common \
    src/debughelper \
    src/defines


DEPENDPATH += \
    src/main \
    src/dialogs/about \
    src/common \
    src/debughelper

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    about.cpp \
    filecommon.cpp \
    debughelper.cpp

HEADERS  += \
    mainwindow.h \
    about.h \
    src/other/defines.h \
    filecommon.h \
    debughelper.h \
    defines.h

FORMS    += \
    mainwindow.ui \
    about.ui

TRANSLATIONS += \
    resources/lang/ru.ts \
    resources/lang/de.ts \
    resources/lang/fr.ts

RESOURCES += \
    resources/resources.qrc
