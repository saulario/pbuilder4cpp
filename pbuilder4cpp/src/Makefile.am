bin_PROGRAMS = pbuilder4cpp
pbuilder4cpp_SOURCES = main.cpp \
	Analyzer.cpp \
	MysqlAnalyzer.cpp \
	OracleAnalyzer.cpp \
	PersistenceBuilder.cpp \
	PostgresqlAnalyzer.cpp \
	Render.cpp \
	SqliteAnalyzer.cpp \
	StringUtils.cpp \
	TNTDBArtifactDeclarationRender.cpp \
	TNTDBArtifactDefinitionRender.cpp \
	TNTDBEntityDeclarationRender.cpp \
	TNTDBEntityDefinitionRender.cpp \
	TNTDBRender.cpp

pbuilder4cpp_CXXFLAGS=--std=c++14 -Wpedantic
pbuilder4cpp_LDADD=-llog4cxx -lboost_program_options -ltntdb -lcxxtools
