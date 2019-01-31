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
				<< std::endl;

			std::cerr << test::dao::CliDAO::remove(con, 2) << std::endl;
			std::cerr << test::dao::CliDAO::remove(con, 2) << std::endl;

		}

		PQexec(con, "ROLLBACK");
		PQexec(con, "BEGIN TRANSACTION");

		test::dao::Param_list plist;
		plist.push_back(test::dao::to_param(0));
		plist.push_back(test::dao::to_param("PERICO PALOTES"));
		std::string stmt = "select * from cli where clicod >= $1 or cliraz = $2";
		test::entity::Cli_list clis = test::dao::CliDAO::query(con, stmt, plist);

		std::cerr << test::dao::CliDAO::remove(con, 4) << std::endl;
		test::entity::Cli_ptr cli1 = std::make_shared<test::entity::Cli>();
		cli1->clicod = 4;
		cli1->cliraz = std::make_shared<std::string>(std::string("jorgito, jaimito y juanito"));
		cli1->cli_smallint.reset();
		test::dao::CliDAO::insert(con, cli1);
		PQexec(con, "COMMIT");


		cli1->cli_smallint = std::make_shared<short>(3);
		test::dao::CliDAO::update(con, cli1);
		PQexec(con, "COMMIT");
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

