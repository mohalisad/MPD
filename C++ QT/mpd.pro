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
    readform.cpp \
    codeassist.cpp \
    changepassform.cpp \
    digitvalidator.cpp \
    editorform.cpp

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
    readform.h \
    codeassist.h \
    changepassform.h \
    digitvalidator.h \
    editorform.h

FORMS    += mainwindow.ui \
    writeform.ui \
    readform.ui \
    changepassform.ui \
    editorform.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    .gitignore

ICON = icons/logo.icns
RC_ICONS = icons/logo.ico
