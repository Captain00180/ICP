QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += -lpthread -lpaho-mqttpp3 -lpaho-mqtt3as

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connectedwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    publishmessage.cpp \
    ../action_callback.cpp \
    ../application_logic.cpp \
    ../topic.cpp


HEADERS += \
    connectedwindow.h \
    mainwindow.h \
    publishmessage.h \
    ../action_callback.h \
    ../application_logic.h \
    ../topic.h


FORMS += \
    connectedwindow.ui \
    mainwindow.ui \
    publishmessage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
