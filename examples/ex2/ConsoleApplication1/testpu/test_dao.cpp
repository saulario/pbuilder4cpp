#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>

#include "libpq-fe.h"
#include "test_dao.h"

using namespace test::dao;

TestDAO::TestDAO()
{
}

TestDAO::~TestDAO()
{
}

test::entity::Test_ptr test::dao::TestDAO::read(PGconn *, long)
{
	return test::entity::Test_ptr();
}

test::entity::Cli_ptr test::dao::CliDAO::read(PGconn * con, int clicod)
{
	test::entity::Cli_ptr retval;

	Oid *paramTypes = NULL;
	const char *paramValues[1];
	int *paramLengths = NULL;
	int paramFormats[1] = { 0 };


	std::stringstream ss;
	ss << clicod;
	std::string p1 = ss.str();

	paramValues[0] = p1.c_str();

	std::cerr << "Parametro--> " << paramValues[0] << std::endl;


	PGresult * result = PQexecParams(con,
		"select * from cli where clicod = $1::int",
		1,
		paramTypes,
		paramValues,
		paramLengths,
		paramFormats,
		0
		);

	std::cerr << "Tuplas: " << PQntuples(result) << std::endl;
	std::cerr << "Columnas: " << PQnfields(result) << std::endl;

	for (int i = 0; i < PQnfields(result); i++) {
		std::cerr 
			<< i << " " << PQfname(result, i)
			<< " " << PQgetvalue(result, 0, i)
			<< std::endl;

	}

	std::string razon = PQgetvalue(result, 0, 1);

	PQclear(result);

	return retval;
}
