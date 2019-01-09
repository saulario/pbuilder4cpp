

//#include "pch.h"
#include <cstdlib>
#include <iostream>
#include <memory>

#include <libpq-fe.h>
#include <test_dao.h>
#include <test_entity.h>

using namespace test::dao;

int main(int argc, char **argv)
{
	PGconn * con = NULL;

	try {
		//con = PQconnectdb("postgresql://postgres:SureStore@localhost/test");
		con = PQconnectdb("postgresql://myrole:myrole123@localhost/mytest?client_encoding=WIN1252");
		ConnStatusType status = PQstatus(con);
		if (status != CONNECTION_OK) {
			throw status;
		}

		auto cli = CliDAO::read(con, 1);



	}
	catch (ConnStatusType t) {
		std::cerr << "Error abriendo base de datos " << t << std::endl;
	}

	PQfinish(con);
	return EXIT_SUCCESS;
}

