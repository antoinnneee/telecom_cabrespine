#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T18:36:33
#
#-------------------------------------------------
QT      += network
QT      += core gui
QT      += androidextras
QT      += bluetooth
QT      += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrabuControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    peermanager.cpp \
    connection.cpp \
    server.cpp \
    androidrfcomm.cpp

HEADERS  += mainwindow.h \
    client.h \
    peermanager.h \
    connection.h \
    server.h \
    androidrfcomm.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 
DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

