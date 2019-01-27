#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>

#include "libpq-fe.h"
#include "test_dao.h"

using namespace test::dao;

bool test::dao::is_error(PGresult * result) {
	ExecStatusType status = PQresultStatus(result);
	return (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK);
}

char ** test::dao::to_param_values(const test::dao::Param_list & param_list) {
	char ** pv = (char **)malloc(sizeof(char *) * param_list.size());

	int index = 0;
	size_t st;
	for (auto p : param_list) {
		st = strlen(p.c_str()) + 1;
		char * buffer = (char *)malloc(sizeof(char) * st);
		strcpy_s(buffer, st, p.c_str());
		pv[index++] = buffer;
	}

	return pv;
}

void test::dao::free_param_values(char **param_values, size_t size) {
	for (int i = 0; i < size; i++) {
		free(param_values[i]);
	}
	free(param_values);
}

template <typename P> Parameter test::dao::to_param(P p) {
	std::stringstream ss;
	ss << p;
	return Parameter(ss.str());
}

template Parameter test::dao::to_param(char const *);

template <typename P> Parameter test::dao::to_param(std::shared_ptr<P> p) {
	if (p) {
		return Parameter(to_param(*p));
	}
	else {
		return Parameter("", true);
	}
}

const char * CliDAO::insert_query = "insert into cli values (clicod, cliraz, cli_smallint, cli_integer, cli_bigint, cli_numeric, cli_numeric_134, cli_real, cli_double, cli_timestamp1, cli_timestamp2, cli_date, cli_time1, cli_time2, cli_interval, cli_boolean, cli_char100, cli_text, cli_point, cli_line, cli_lseg, cli_box, cli_path, cli_polygon, cli_circle, cli_cidr, cli_inet, cli_macaddr, cli_macaddr8, cli_bit10, cli_bitv10, cli_uuid, cli_xml, cli_json, cli_jsonb)";
const char * CliDAO::read_query = "select clicod, cliraz, cli_smallint, cli_integer, cli_bigint, cli_numeric, cli_numeric_134, cli_real, cli_double, cli_timestamp1, cli_timestamp2, cli_date, cli_time1, cli_time2, cli_interval, cli_boolean, cli_char100, cli_text, cli_point, cli_line, cli_lseg, cli_box, cli_path, cli_polygon, cli_circle, cli_cidr, cli_inet, cli_macaddr, cli_macaddr8, cli_bit10, cli_bitv10, cli_uuid, cli_xml, cli_json, cli_jsonb from cli where clicod = $1";
const char * CliDAO::remove_query = "delete from cli where clicod = $1";
//const char * CliDAO::update_query = "update cli set clicod, cliraz, cli_smallint, cli_integer, cli_bigint, cli_numeric, cli_numeric_134, cli_real, cli_double, cli_timestamp1, cli_timestamp2, cli_date, cli_time1, cli_time2, cli_interval, cli_boolean, cli_char100, cli_text, cli_point, cli_line, cli_lseg, cli_box, cli_path, cli_polygon, cli_circle, cli_cidr, cli_inet, cli_macaddr, cli_macaddr8, cli_bit10, cli_bitv10, cli_uuid, cli_xml, cli_json, cli_jsonb where clicod = $1";
const char * CliDAO::update_query = "update cli set clicod = $1, cliraz = $2 where clicod = $3";

test::entity::Cli_ptr CliDAO::insert(PGconn *con, test::entity::Cli_ptr cli) {
	return cli;
}

test::entity::Cli_ptr CliDAO::read(PGconn * con, int clicod)
{
	test::entity::Cli_ptr retval;

	Param_list pl;
	pl.push_back(to_param(clicod));
	char **pv = to_param_values(pl);

	PGresult * result = PQexecParams(con, read_query, (int)pl.size(), NULL, pv, NULL, NULL, 0);
	if (is_error(result)) {
		throw std::runtime_error(PQresultErrorMessage(result));
	}
	if (PQntuples(result)) {
		retval = load_columns(result);
	}

	free_param_values(pv, pl.size());
	PQclear(result);
	return retval;
}

test::entity::Cli_list CliDAO::query(PGconn * con, const std::string & stmt, const Param_list & pl) {
	test::entity::Cli_list retval;

	char ** pv = to_param_values(pl);

	PGresult * result = PQexecParams(con, stmt.c_str(), (int)pl.size(), NULL, pv, NULL, NULL, 0);
	if (is_error(result)) {
		throw std::runtime_error(PQresultErrorMessage(result));
	}
	for (int row_number = 0; row_number < PQntuples(result); row_number++) {
		retval.push_back(load_columns(result, row_number));
	}

	free_param_values(pv, pl.size());
	PQclear(result);
	return retval;
}

int CliDAO::remove(PGconn *con, int clicod) {
	int retval;

	const char *pv[1];
	auto p1 = to_param(clicod);
	pv[0] = p1.c_str();

	PGresult * result = PQexecParams(con, remove_query, 1, NULL, pv, NULL, NULL, 0);
	if (is_error(result)) {
		throw std::runtime_error(PQresultErrorMessage(result));
	}
	retval = (int)strtol(PQcmdTuples(result), NULL, 0);

	PQclear(result);
	return retval;
}

test::entity::Cli_ptr CliDAO::update(PGconn *con, test::entity::Cli_ptr cli) {

	Parameter pb[2];
	pb[0] = to_param(cli->clicod);
	pb[1] = to_param(cli->cliraz);

	const char *pv[3];
	pv[0] = pb[0].c_str();
	pv[1] = pb[1].c_str();





	return cli;
}

test::entity::Cli_ptr CliDAO::load_columns(PGresult * result, int row_number) {
	test::entity::Cli_ptr cli = std::make_shared<test::entity::Cli>();
	int index = 0;
	cli->clicod = std::atoi(PQgetvalue(result, row_number, index++));
	if (PQgetisnull(result, row_number, index)) {
		cli->cliraz.reset();
	}
	else {
		cli->cliraz = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_smallint.reset();
	}
	else {
		cli->cli_smallint = std::make_shared<short>(std::atoi(PQgetvalue(result, row_number, index)));
	}
	index++;



	return cli;
}

//test::entity::Cli_ptr CliDAO::load_columns(PGresult * result) {
//	test::entity::Cli_ptr cli = std::make_unique<test::entity::Cli>();
//	int index = 0;
//	cli->clicod = std::atoi(PQgetvalue(result, 0, index++));
//	cli->cliraz = PQgetisnull(result, 0, index) ? NULL : std::make_unique<std::string>(std::string(PQgetvalue(result, 0, index++)));
//	cli->cli_smallint = PQgetisnull(result, 0, index) ? NULL : std::make_unique<short>(std::atoi(PQgetvalue(result, 0, index++)));
//	cli->cli_integer = PQgetisnull(result, 0, index) ? NULL : std::make_unique<int>(std::atoi(PQgetvalue(result, 0, index++)));
//	cli->cli_bigint = PQgetisnull(result, 0, index) ? NULL : std::make_unique<long>(std::atol(PQgetvalue(result, 0, index++)));
//	cli->cli_numeric = PQgetisnull(result, 0, index) ? NULL : std::make_unique<double>(std::atof(PQgetvalue(result, 0, index++)));
//	cli->cli_numeric_134 = PQgetisnull(result, 0, index) ? NULL : std::make_unique<double>(std::atof(PQgetvalue(result, 0, index++)));
//	cli->cli_real = PQgetisnull(result, 0, index) ? NULL : std::make_unique<double>(std::atof(PQgetvalue(result, 0, index++)));
//	cli->cli_double = PQgetisnull(result, 0, index) ? NULL : std::make_unique<double>(std::atof(PQgetvalue(result, 0, index++)));
//	return cli;
//}