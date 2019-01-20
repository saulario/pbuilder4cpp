#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>

#include "libpq-fe.h"

class Parameter {
public:
	Parameter(const std::string & p_buffer, bool is_null = false) :
		buffer(p_buffer), null_param(is_null) {
	}

	const char * c_str(void) {
		return (is_null() ? NULL : buffer.c_str());
	}

	inline bool is_null(void) { return null_param; }
	inline bool not_null(void) { return !is_null(); }

private:
	bool null_param;
	std::string buffer;
};

template <typename P> Parameter to_param(P p) {
	std::stringstream ss;
	ss << p;
	return Parameter(ss.str());
}

template <typename P> Parameter to_param(std::shared_ptr<P> p) {
	if (p) {
		return Parameter(to_param(*p));
	}
	else {
		return Parameter("", true);
	}
}


void test1(PGconn * con) {

	std::cerr << "*** Test1 ***" << std::endl;

	std::string cmd = "select * from cli where clicod = $1::int";
	const char *pv[1];

	Parameter p = to_param(1);
	pv[0] = p.c_str();

	PGresult *res = PQexecParams(con, cmd.c_str(), 1, NULL, pv, NULL, NULL, 0);
	std::cerr << "Resultados: " << PQcmdTuples(res) << std::endl;

	int clicod = atoi(PQgetvalue(res, 0, 0));
	std::unique_ptr<std::string> cliraz = PQgetisnull(res, 0, 1) ? NULL
		: std::make_unique<std::string>(PQgetvalue(res, 0, 1));

	std::cerr << "Codigo: " << clicod << " razon: " << (*cliraz).c_str() << std::endl;

	PQclear(res);
}

void test2(PGconn *con) {
	std::cerr << "*** Test2 ***" << std::endl;

	PGresult *res = PQexecParams(con, "begin", 0, NULL, NULL, NULL, NULL, 0);
	PQclear(res);

	Parameter clicod = to_param(2);
	std::string cliraz = "EL CLIENTE NÚMERO 2";

	const char *pv[2];
	pv[0] = clicod.c_str();
	pv[1] = cliraz.c_str();

	std::string cmd = "insert into cli (clicod, cliraz) values ($1, $2)";
	res = PQexecParams(con, cmd.c_str(), 2, NULL, pv, NULL, NULL, 0);
	std::cerr << "Resultados: " << PQcmdTuples(res) << std::endl;

	PQclear(res);

	res = PQexecParams(con, "commit", 0, NULL, NULL, NULL, NULL, 0);
	PQclear(res);
}

void test3(PGconn *con) {
	std::cerr << "*** Test3 ***" << std::endl;
	PGresult *res = PQexecParams(con, "delete from cli where clicod = 2", 0, NULL, NULL, NULL, NULL, 0);
	std::cerr << "Resultados: " << PQcmdTuples(res) << std::endl;
	PQclear(res);
}

void test4(PGconn *con) {
	std::cerr << "*** Test4 ***" << std::endl;

	PGresult *res = PQexecParams(con, "begin", 0, NULL, NULL, NULL, NULL, 0);
	PQclear(res);

	Parameter clicod = to_param(2);

	const char *pv[2];
	pv[0] = clicod.c_str();
	pv[1] = NULL;

	std::string cmd = "insert into cli (clicod, cliraz) values ($1, $2)";
	res = PQexecParams(con, cmd.c_str(), 2, NULL, pv, NULL, NULL, 0);
	std::cerr << "Resultados: " << PQcmdTuples(res) << std::endl;

	PQclear(res);

	res = PQexecParams(con, "commit", 0, NULL, NULL, NULL, NULL, 0);
	PQclear(res);
}



void test51(PGconn *con, int pclicod, std::shared_ptr<std::string> pcliraz) {

	auto clicod = to_param(pclicod);
	auto cliraz = to_param(pcliraz);

	int index = 0;
	const char **pv = (const char **)malloc(sizeof(char *) * 2);
	pv[0] = clicod.c_str();
	pv[1] = cliraz.c_str();

	std::cerr << "0: " << pv[0] << std::endl;
	std::cerr << "1: " << pv[1] << std::endl;

	std::string query = "select * from cli where clicod = $1 or cliraz like $2";
	PGresult *res = PQexecParams(con, query.c_str(), 2, NULL, pv, NULL, NULL, 0);

	std::cerr << "Filas: " << PQntuples(res) << std::endl;

	free(pv);
	PQclear(res);
}

void test5(PGconn *con) {
	std::cerr << "*** Test5 ***" << std::endl;

	int clicod = 2;
	std::shared_ptr<std::string> cliraz = std::make_shared<std::string>("ESTE NO ES NULO");
	test51(con, clicod, cliraz);

	//clicod = 3;
	//cliraz.reset();
	//test51(con, clicod, cliraz);
}

int main(int argc, char **argv) {

	PGconn * con = NULL;

	try {
		con = PQconnectdb("postgresql://myrole:myrole123@localhost/mytest?client_encoding=WIN1252");
		ConnStatusType status = PQstatus(con);
		if (status != CONNECTION_OK) {
			throw status;
		}

		//test1(con);
		//test2(con);
		//test3(con);
		//test4(con);
		test5(con);





	}
	catch (ConnStatusType t) {
		std::cerr << "Error abriendo base de datos " << t << std::endl;
	}

	PQfinish(con);
	return EXIT_SUCCESS;
}