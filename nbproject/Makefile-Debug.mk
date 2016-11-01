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
OBJECTFILES= \
	${OBJECTDIR}/client.o \
	${OBJECTDIR}/fileClass.o \
	${OBJECTDIR}/fsmClient.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/packetManager.o


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
LDLIBSOPTIONS=`pkg-config --libs ncurses` `pkg-config --libs apr-1`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/client

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/client: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/client ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/client.o: client.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags ncurses` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/client.o client.cpp

${OBJECTDIR}/fileClass.o: fileClass.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags ncurses` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fileClass.o fileClass.cpp

${OBJECTDIR}/fsmClient.o: fsmClient.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags ncurses` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fsmClient.o fsmClient.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags ncurses` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/packetManager.o: packetManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags ncurses` `pkg-config --cflags apr-1` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/packetManager.o packetManager.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/client

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
