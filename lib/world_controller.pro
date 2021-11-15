QT -= gui

TEMPLATE = lib
DEFINES += EXPORT_LIBRARY

CONFIG += c++17

SOURCES += \
    WorldController.cpp

HEADERS += \
    export_library_global.h \
    WorldController.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
