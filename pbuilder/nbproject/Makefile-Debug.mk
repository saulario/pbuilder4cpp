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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/pbuilder_PersistenceBuilder.o \
	${OBJECTDIR}/pbuilder_analyzer_Analyzer.o \
	${OBJECTDIR}/pbuilder_analyzer_MysqlAnalyzer.o \
	${OBJECTDIR}/pbuilder_analyzer_OracleAnalyzer.o \
	${OBJECTDIR}/pbuilder_analyzer_PostgresqlAnalyzer.o \
	${OBJECTDIR}/pbuilder_analyzer_SqliteAnalyzer.o \
	${OBJECTDIR}/pbuilder_render_Render.o \
	${OBJECTDIR}/pbuilder_render_TNTDBRender.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 --std=c++0x
CXXFLAGS=-m64 --std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-llog4cxx -lboost_program_options -lboost_system -ltntdb

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pbuilder

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pbuilder: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pbuilder ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/pbuilder_PersistenceBuilder.o: pbuilder_PersistenceBuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/pbuilder_PersistenceBuilder.o pbuilder_PersistenceBuilder.cpp

${OBJECTDIR}/pbuilder_analyzer_Analyzer.o: pbuilder_analyzer_Analyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/pbuilder_analyzer_Analyzer.o pbuilder_analyzer_Analyzer.cpp

${OBJECTDIR}/pbuilder_analyzer_MysqlAnalyzer.o: pbuilder_analyzer_MysqlAnalyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/pbuilder_analyzer_MysqlAnalyzer.o pbuilder_analyzer_MysqlAnalyzer.cpp

${OBJECTDIR}/pbuilder_analyzer_OracleAnalyzer.o: pbuilder_analyzer_OracleAnalyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/pbuilder_analyzer_OracleAnalyzer.o pbuilder_analyzer_OracleAnalyzer.cpp

${OBJECTDIR}/pbuilder_analyzer_PostgresqlAnalyzer.o: pbuilder_analyzer_PostgresqlAnalyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/pbuilder_analyzer_PostgresqlAnalyzer.o pbuilder_analyzer_PostgresqlAnalyzer.cpp

${OBJECTDIR}/pbuilder_analyzer_SqliteAnalyzer.o: pbuilder_analyzer_SqliteAnalyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/pbuilder_analyzer_SqliteAnalyzer.o pbuilder_analyzer_SqliteAnalyzer.cpp

${OBJECTDIR}/pbuilder_render_Render.o: pbuilder_render_Render.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/pbuilder_render_Render.o pbuilder_render_Render.cpp

${OBJECTDIR}/pbuilder_render_TNTDBRender.o: pbuilder_render_TNTDBRender.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/pbuilder_render_TNTDBRender.o pbuilder_render_TNTDBRender.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pbuilder

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
