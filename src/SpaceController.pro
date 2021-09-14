QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32{
DESTDIR = ../bin_win
}
unix{
DESTDIR = ../bin_linux
}

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# EasyShape
SOURCES += \
    EasyShape/EasyPoint2D.cpp \
    EasyShape/EasyRect2D.cpp \
    EasyShape/EasyLine2D.cpp \
    EasyShape/EasyIntersection2D.cpp \
    EasyShape/EasyPolygon2D.cpp \
    EasyShape/EasyComputation.cpp

HEADERS += \
    EasyShape/EasyPoint2D.h \
    EasyShape/EasyRect2D.h \
    EasyShape/EasyLine2D.h \
    EasyShape/EasyIntersection2D.h \
    EasyShape/EasyPolygon2D.h \
    EasyShape/EasyComputation.h

# SpaceController
SOURCES += \
    SpaceController/BoundaryController.cpp \
    SpaceController/SpaceController.cpp

HEADERS += \
    SpaceController/BoundaryController.h \
    SpaceController/SpaceController.h

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

FORMS += \
    MainWindow.ui

TRANSLATIONS += \
    SpaceController_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
