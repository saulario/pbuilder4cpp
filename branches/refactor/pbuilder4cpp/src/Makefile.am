bin_PROGRAMS = pbuilder4cpp
pbuilder4cpp_SOURCES = main.cpp \
	Analyzer.cpp \
	PersistenceBuilder.cpp \
	Render.cpp \
	analyzer/MysqlAnalyzer.cpp \
	analyzer/OracleAnalyzer.cpp \
	analyzer/PostgresqlAnalyzer.cpp \
	analyzer/SqliteAnalyzer.cpp \
	tntdb/TNTDBArtifactDeclarationRender.cpp \
	tntdb/TNTDBArtifactDefinitionRender.cpp \
	tntdb/TNTDBEntityDeclarationRender.cpp \
	tntdb/TNTDBEntityDefinitionRender.cpp \
	tntdb/TNTDBRender.cpp

pbuilder4cpp_CXXFLAGS=--std=c++0x 
pbuilder4cpp_LDADD=-llog4cxx -lboost_program_options -ltntdb
