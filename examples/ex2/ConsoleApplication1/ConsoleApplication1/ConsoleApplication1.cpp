#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <utility>

#include <libpq-fe.h>
#include <test_dao.h>
#include <test_entity.h>

//using namespace test::dao;

int main(int argc, char **argv)
{
	PGconn * con = NULL;

	try {
		con = PQconnectdb("postgresql://myrole:myrole123@localhost/mytest?client_encoding=WIN1252");
		ConnStatusType status = PQstatus(con);
		if (status != CONNECTION_OK) {
			throw status;
		}

		PQexec(con, "BEGIN TRANSACTION");

		auto cli = test::dao::CliDAO::read(con, 1);
		if (cli) {
			std::cerr
				<< cli->clicod << " "
				<< (*cli->cliraz).c_str() << " "
				<< *cli->cli_smallint << " "
				//<< *cli->cli_integer << " "
				//<< *cli->cli_bigint << " "
				//<< *cli->cli_numeric << " "
				//<< *cli->cli_numeric_134 << " "
				//<< *cli->cli_real << " "
				//<< *cli->cli_double << " "
				<< std::endl;



			std::cerr << "aqui estoy" << std::endl;

			std::cerr << test::dao::CliDAO::remove(con, 2) << std::endl;
			std::cerr << test::dao::CliDAO::remove(con, 2) << std::endl;

		}

		test::dao::Param_list plist;
		plist.push_back(test::dao::to_param(0));
		plist.push_back(test::dao::to_param("PERICO PALOTES"));
		std::string stmt = "select * from cli where clicod >= $1 or cliraz = $2";
		test::entity::Cli_list clis = test::dao::CliDAO::query(con, stmt, plist);

	}
	catch (ConnStatusType t) {
		std::cerr << "Error abriendo base de datos " << t << std::endl;
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}

	PQfinish(con);
	return EXIT_SUCCESS;
}

