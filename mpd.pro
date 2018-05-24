#-------------------------------------------------
#
# Project created by QtCreator 2018-05-23T00:58:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diaryui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cryptor.cpp \
    date.cpp \
    diary.cpp \
    entry.cpp \
    exception.cpp \
    random.cpp \
    sha256.cpp \
    strlib.cpp \
    strtoken.cpp \
    writeform.cpp \
    uiassist.cpp \
    readform.cpp

HEADERS  += mainwindow.h \
    cryptor.h \
    date.h \
    diary.h \
    entry.h \
    exception.h \
    random.h \
    sha256.h \
    strlib.h \
    strtoken.h \
    writeform.h \
    uiassist.h \
    readform.h

FORMS    += mainwindow.ui \
    writeform.ui \
    readform.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    .gitignore
