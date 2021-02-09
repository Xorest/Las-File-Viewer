QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= debug_and_relase
DESTDIR = build
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    converter.cpp \
    file.cpp \
    headerfile.cpp \
    main.cpp \
    mainwindow.cpp \
    openglwidget.cpp \
    pointdatarecords.cpp \
    variablelengthrecordsfile.cpp

HEADERS += \
    camera.h \
    converter.h \
    file.h \
    headerfile.h \
    mainwindow.h \
    openglwidget.h \
    pointdatarecords.h \
    variablelengthrecordsfile.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
