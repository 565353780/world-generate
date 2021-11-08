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

# OpenCV
unix{
INCLUDEPATH += \
    /home/chli/OpenCV/opencv-3.4.10/build/installed/include \
    /home/chli/OpenCV/opencv-3.4.10/build/installed/include/opencv \
    /home/chli/OpenCV/opencv-3.4.10/build/installed/include/opencv2

LIBS += \
    -L/home/chli/OpenCV/opencv-3.4.10/build/installed/lib \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_imgcodecs \
    -lopencv_highgui
}

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

HEADERS += \
    EasyShape/EasyShape.h

# EasyWorld
SOURCES += \
    EasyWorld/EasyAxis2D.cpp \
    EasyWorld/EasyNode.cpp \
    EasyWorld/EasyTree.cpp \
    EasyWorld/WorldController.cpp \
    EasyWorld/WorldPlaceGenerator.cpp \
    EasyWorld/WorldDescriptor.cpp \
    EasyWorld/WorldEditor.cpp \
    EasyWorld/WorldReward.cpp

HEADERS += \
    EasyWorld/EasyAxis2D.h \
    EasyWorld/EasyNode.h \
    EasyWorld/EasyTree.h \
    EasyWorld/WorldController.h \
    EasyWorld/WorldPlaceGenerator.h \
    EasyWorld/WorldDescriptor.h \
    EasyWorld/WorldEditor.h \
    EasyWorld/WorldReward.h

HEADERS += \
    EasyWorld/EasyWorld.h

SOURCES += \
    main.cpp \
    EasyWorldWidget.cpp \
    MainWindow.cpp

HEADERS += \
    EasyWorldWidget.h \
    MainWindow.h

FORMS += \
    EasyWorldWidget.ui \
    MainWindow.ui

TRANSLATIONS += \
    SpaceController_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

