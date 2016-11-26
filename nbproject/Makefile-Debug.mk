#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as
QMAKE=qmake

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES=


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs gstreamer-1.0` `pkg-config --libs gstreamer-allocators-1.0` `pkg-config --libs gstreamer-app-1.0` `pkg-config --libs gstreamer-audio-1.0` `pkg-config --libs gstreamer-base-1.0` `pkg-config --libs gstreamer-check-1.0` `pkg-config --libs gstreamer-controller-1.0` `pkg-config --libs gstreamer-fft-1.0` `pkg-config --libs gstreamer-net-1.0` `pkg-config --libs gstreamer-pbutils-1.0` `pkg-config --libs gstreamer-plugins-base-1.0` `pkg-config --libs gstreamer-riff-1.0` `pkg-config --libs gstreamer-rtp-1.0` `pkg-config --libs gstreamer-rtsp-1.0` `pkg-config --libs gstreamer-sdp-1.0` `pkg-config --libs gstreamer-tag-1.0` `pkg-config --libs gstreamer-video-1.0` `pkg-config --libs glib-2.0`  

nbproject/qt-${CND_CONF}.mk: nbproject/qt-${CND_CONF}.pro FORCE
	${QMAKE} VPATH=. -o qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.pro
	mv -f qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.mk

FORCE:

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	"${MAKE}" -f nbproject/qt-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/CarGUI

${CND_BUILDDIR}/Debug/%.o: nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk "$@"

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk distclean

# Subprojects
.clean-subprojects:
