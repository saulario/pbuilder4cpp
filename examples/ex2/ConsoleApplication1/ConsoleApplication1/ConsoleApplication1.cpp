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
				<< *cli->cli_integer << " "
				<< *cli->cli_bigint << " "
				<< *cli->cli_numeric << " "
				<< *cli->cli_numeric_134 << " "
				<< *cli->cli_real << " "
				<< *cli->cli_double << " "
				<< (cli->cli_timestamp1 ? (*cli->cli_timestamp1).c_str() : " ") << " "
				<< (cli->cli_timestamp2 ? (*cli->cli_timestamp2).c_str() : " ") << " "
				<< (cli->cli_date ? (*cli->cli_date).c_str() : " ") << " "
				<< (cli->cli_time1 ? (*cli->cli_time1).c_str() : " ") << " "
				<< (cli->cli_time2 ? (*cli->cli_time2).c_str() : " ") << " "
				<< (cli->cli_interval ? (*cli->cli_interval).c_str() : " ") << " "
				<< (cli->cli_boolean ? (*cli->cli_boolean).c_str() : " ") << " "
				<< (cli->cli_char100 ? (*cli->cli_char100).c_str() : " ") << " "
				<< (cli->cli_text ? (*cli->cli_text).c_str() : " ") << " "
				<< (cli->cli_point ? (*cli->cli_point).c_str() : " ") << " "
				<< (cli->cli_line ? (*cli->cli_line).c_str() : " ") << " "
				<< (cli->cli_boolean ? (*cli->cli_boolean).c_str() : " ") << " "
				<< (cli->cli_lseg ? (*cli->cli_lseg).c_str() : " ") << " "
				<< (cli->cli_box ? (*cli->cli_box).c_str() : " ") << " "
				<< (cli->cli_path ? (*cli->cli_path).c_str() : " ") << " "
				<< (cli->cli_polygon ? (*cli->cli_polygon).c_str() : " ") << " "
				<< (cli->cli_circle ? (*cli->cli_circle).c_str() : " ") << " "
				<< (cli->cli_cidr ? (*cli->cli_cidr).c_str() : " ") << " "
				<< (cli->cli_inet ? (*cli->cli_inet).c_str() : " ") << " "	
				<< (cli->cli_macaddr ? (*cli->cli_macaddr).c_str() : " ") << " "
				<< (cli->cli_macaddr8 ? (*cli->cli_macaddr8).c_str() : " ") << " "
				<< (cli->cli_boolean ? (*cli->cli_boolean).c_str() : " ") << " "
				<< (cli->cli_bit10 ? (*cli->cli_bit10).c_str() : " ") << " "
				<< (cli->cli_bitv10 ? (*cli->cli_bitv10).c_str() : " ") << " "
				<< (cli->cli_uuid ? (*cli->cli_uuid).c_str() : " ") << " "
				<< (cli->cli_xml ? (*cli->cli_xml).c_str() : " ") << " "
				<< (cli->cli_json ? (*cli->cli_json).c_str() : " ") << " "
				<< (cli->cli_jsonb ? (*cli->cli_jsonb).c_str() : " ") << " "
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

		PQexec(con, "BEGIN TRANSACTION");
		cli1->cli_smallint = std::make_shared<short>(3);
		test::dao::CliDAO::update(con, cli1);
		PQexec(con, "COMMIT");

		PQexec(con, "BEGIN TRANSACTION");
		cli->clicod = 10;
		test::dao::CliDAO::insert(con, cli);
		PQexec(con, "COMMIT");

		PQexec(con, "BEGIN TRANSACTION");
		test::dao::CliDAO::remove(con, 10);
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

