QT -= gui
QT += network

TEMPLATE = lib
DEFINES += MYUDPLIB_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hermes.cpp \
    myudplib.cpp \
    udpclient.cpp \
    udpserver.cpp

HEADERS += \
    Helper.h \
    MyUDPLib_global.h \
    hermes.h \
    myudplib.h \
    udpclient.h \
    udpserver.h

# Default rules for deployment.
unix {
    target.path = /usr/local/lib/
}
mac {
    target.path = /usr/local/lib/
}

!isEmpty(target.path): INSTALLS += target
