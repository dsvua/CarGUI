# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = CarGUI
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets network opengl
SOURCES += Conf.cpp.cc MainWindow.cpp.cc main.cpp
HEADERS += Conf.h MainWindow.h
FORMS += Conf.ui MainWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/include/glib-2.0 /usr/lib/x86_64-linux-gnu/glib-2.0/include /usr/include/gstreamer-1.0 /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include /usr/local/include/Qt5GStreamer 
LIBS += -Wl,-rpath,/usr/local/lib /usr/local/lib/libQt5GStreamer-1.0.so -Wl,-rpath,/usr/local/lib /usr/local/lib/libQt5GStreamerUi-1.0.so -Wl,-rpath,/usr/lib/x86_64-linux-gnu/gstreamer-1.0 /usr/lib/x86_64-linux-gnu/gstreamer-1.0/libgstqt5videosink.so -Wl,-rpath,/usr/local/lib /usr/local/lib/libQt5GLib-2.0.so  
