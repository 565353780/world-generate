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
    EasyShape/EasyComputation.h \

HEADERS += \
    EasyShape/EasyShape.h

# EasySpace
SOURCES += \
    EasySpace/EasyBoundary.cpp \
    EasySpace/EasyRoom.cpp \
    EasySpace/EasyBoundaryPoint.cpp \
    EasySpace/EasyBoundaryLine.cpp \
    EasySpace/EasyRoomLine.cpp \
    EasySpace/SpaceController.cpp

HEADERS += \
    EasySpace/EasyBoundary.h \
    EasySpace/EasyRoom.h \
    EasySpace/EasyBoundaryPoint.h \
    EasySpace/EasyBoundaryLine.h \
    EasySpace/EasyRoomLine.h \
    EasySpace/SpaceController.h

HEADERS += \
    EasySpace/EasySpace.h

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
