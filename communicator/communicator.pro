#-------------------------------------------------
#
# Project created by QtCreator 2021-01-10T09:53:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = communicator
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/setpassworddialog.cpp \
    src/cryptography.cpp \
    src/newcontactdialog.cpp \
    src/tcpconnector.cpp \
    src/checkpassworddialog.cpp \
    src/contact.cpp


HEADERS  += head/mainwindow.h \
    head/setpassworddialog.h \
    head/cryptography.h \
    head/newcontactdialog.h \
    head/tcpconnector.h \
    head/checkpassworddialog.h \
    head/generalvariables.h \
    head/contact.h

FORMS    += ui/mainwindow.ui \
    ui/setpassworddialog.ui \
    ui/newcontactdialog.ui \
    ui/checkpassworddialog.ui

DISTFILES += \
    .txt/contactList.txt \
    .txt/password.txt

LIBS += -lcryptopp
