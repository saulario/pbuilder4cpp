#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>

#include "libpq-fe.h"
#include "test_dao.h"

using namespace test::dao;

template <typename P> Parameter test::dao::to_param(P p) {
	std::stringstream ss;
	ss << p;
	return Parameter(ss.str());
}

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
const char * CliDAO::remove_query = "delete from cli where clicod = $1:int";
//const char * CliDAO::update_query = "update cli set clicod, cliraz, cli_smallint, cli_integer, cli_bigint, cli_numeric, cli_numeric_134, cli_real, cli_double, cli_timestamp1, cli_timestamp2, cli_date, cli_time1, cli_time2, cli_interval, cli_boolean, cli_char100, cli_text, cli_point, cli_line, cli_lseg, cli_box, cli_path, cli_polygon, cli_circle, cli_cidr, cli_inet, cli_macaddr, cli_macaddr8, cli_bit10, cli_bitv10, cli_uuid, cli_xml, cli_json, cli_jsonb where clicod = $1";
const char * CliDAO::update_query = "update cli set clicod = $1, cliraz = $2 where clicod = $3";

test::entity::Cli_ptr CliDAO::insert(PGconn *con, test::entity::Cli_ptr cli) {

	return cli;
}

test::entity::Cli_ptr CliDAO::read(PGconn * con, int clicod)
{
	test::entity::Cli_ptr retval;

	Oid *pt = NULL;
	const char *pv[1];
	int *pl = NULL;
	int pf[1] = { 0 };

	auto p1 = to_param(clicod);
	pv[0] = p1.c_str();

	PGresult * result = PQexecParams(con, read_query, 1, pt, pv, pl, pf, 0);
	if (PQntuples(result)) {
		retval = load_columns(result);
	}

	PQclear(result);
	return retval;
}

int CliDAO::remove(PGconn *con, test::entity::Cli_ptr cli) {
	int result = 0;

	return result;
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

test::entity::Cli_ptr CliDAO::load_columns(PGresult * result) {
	test::entity::Cli_ptr cli = std::make_unique<test::entity::Cli>();
	int index = 0;
	cli->clicod = std::atoi(PQgetvalue(result, 0, index++));
	cli->cliraz = PQgetisnull(result, 0, index) ? NULL : std::make_unique<std::string>(std::string(PQgetvalue(result, 0, index++)));
	cli->cli_smallint = PQgetisnull(result, 0, index) ? NULL : std::make_unique<short>(std::atoi(PQgetvalue(result, 0, index++)));
	cli->cli_integer = PQgetisnull(result, 0, index) ? NULL : std::make_unique<int>(std::atoi(PQgetvalue(result, 0, index++)));
	cli->cli_bigint = PQgetisnull(result, 0, index) ? NULL : std::make_unique<long>(std::atol(PQgetvalue(result, 0, index++)));
	cli->cli_numeric = PQgetisnull(result, 0, index) ? NULL : std::make_unique<double>(std::atof(PQgetvalue(result, 0, index++)));
	cli->cli_numeric_134 = PQgetisnull(result, 0, index) ? NULL : std::make_unique<double>(std::atof(PQgetvalue(result, 0, index++)));
	cli->cli_real = PQgetisnull(result, 0, index) ? NULL : std::make_unique<double>(std::atof(PQgetvalue(result, 0, index++)));
	cli->cli_double = PQgetisnull(result, 0, index) ? NULL : std::make_unique<double>(std::atof(PQgetvalue(result, 0, index++)));
	return cli;
}