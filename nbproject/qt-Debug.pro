# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = CarGUI
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += link_pkgconfig debug 
PKGCONFIG += gstreamer-1.0 gstreamer-allocators-1.0 gstreamer-app-1.0 gstreamer-audio-1.0 gstreamer-base-1.0 gstreamer-check-1.0 gstreamer-controller-1.0 gstreamer-fft-1.0 gstreamer-net-1.0 gstreamer-pbutils-1.0 gstreamer-plugins-base-1.0 gstreamer-riff-1.0 gstreamer-rtp-1.0 gstreamer-rtsp-1.0 gstreamer-sdp-1.0 gstreamer-tag-1.0 gstreamer-video-1.0 glib-2.0
QT = core gui widgets network opengl
SOURCES += /home/serhiy/NetBeansProjects/CarGUI/StreamRtpClient.cpp MainWindow.cpp.cc main.cpp
HEADERS += /home/serhiy/NetBeansProjects/CarGUI/StreamRtpClient.h MainWindow.h
FORMS += MainWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/include/glib-2.0 /usr/lib/x86_64-linux-gnu/glib-2.0/include /usr/include/gstreamer-1.0 /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include 
LIBS += 
