QT += qml quick

REGINE_ROOT = $$PWD
INCLUDEPATH+= $$REGINE_ROOT

HEADERS += \
    $$REGINE_ROOT/core/rstorage.h \
    $$REGINE_ROOT/regine.h \
    regine/core/gamewindow.h

SOURCES += \
    $$REGINE_ROOT/core/rstorage.cpp \
    $$REGINE_ROOT/regine.cpp \
    regine/core/gamewindow.cpp
