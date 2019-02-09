#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "libpq-fe.h"





int main(int argc, char **argv) {

	PGconn * con = NULL;

	try {
		con = PQconnectdb("postgresql://myrole:myrole123@localhost/mytest?client_encoding=WIN1252");
		ConnStatusType status = PQstatus(con);
		if (status != CONNECTION_OK) {
			throw status;
		}

	}
	catch (ConnStatusType t) {
		std::cerr << "Error abriendo base de datos " << t << std::endl;
	}

	PQfinish(con);
	return EXIT_SUCCESS;
}