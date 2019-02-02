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
		char * buffer = NULL;
		if (p.not_null()) {
			st = strlen(p.c_str()) + 1;
			buffer = (char *)malloc(sizeof(char) * st);
			strcpy_s(buffer, st, p.c_str());
		}
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

const char * CliDAO::insert_query = "insert into cli("
	" clicod, cliraz, cli_smallint, cli_integer, cli_bigint "
	", cli_numeric, cli_numeric_134, cli_real, cli_double, cli_timestamp1 "
	", cli_timestamp2, cli_date, cli_time1, cli_time2, cli_interval "
	", cli_boolean, cli_char100, cli_text, cli_point, cli_line"
	", cli_lseg, cli_box, cli_path, cli_polygon, cli_circle"
	", cli_cidr, cli_inet, cli_macaddr, cli_macaddr8, cli_bit10"
	", cli_bitv10, cli_uuid, cli_xml, cli_json, cli_jsonb"
	") values ("
	" $1,$2,$3,$4,$5,$6,$7,$8,$9,$10"
	",$11,$12,$13,$14,$15,$16,$17,$18,$19,$20"
	",$21,$22,$23,$24,$25,$26,$27,$28,$29,$30"
	",$31,$32,$33,$34,$35"
	")";
const char * CliDAO::read_query = "select "
	" clicod, cliraz, cli_smallint, cli_integer, cli_bigint"
	", cli_numeric, cli_numeric_134, cli_real, cli_double, cli_timestamp1"
	", cli_timestamp2, cli_date, cli_time1, cli_time2, cli_interval"
	", cli_boolean, cli_char100, cli_text, cli_point, cli_line"
	", cli_lseg, cli_box, cli_path, cli_polygon, cli_circle"
	", cli_cidr, cli_inet, cli_macaddr, cli_macaddr8, cli_bit10"
	", cli_bitv10, cli_uuid, cli_xml, cli_json, cli_jsonb"
	" from cli where "
	" clicod = $1";
const char * CliDAO::remove_query = "delete from cli where clicod = $1";
const char * CliDAO::update_query = "update cli set "
	" clicod=$1, cliraz=$2, cli_smallint=$3, cli_integer=$4, cli_bigint=$5 "
	", cli_numeric=$6, cli_numeric_134=$7, cli_real=$8, cli_double=$9, cli_timestamp1=$10"
	", cli_timestamp2=$11, cli_date=$12, cli_time1=$13, cli_time2=$14, cli_interval=$15 "
	", cli_boolean=$16, cli_char100=$17, cli_text=$18, cli_point=$19, cli_line=$20 "
	", cli_lseg=$21, cli_box=$22, cli_path=$23, cli_polygon=$24, cli_circle=$25 "
	", cli_cidr=$26, cli_inet=$27, cli_macaddr=$28, cli_macaddr8=$29, cli_bit10=$30 "
	", cli_bitv10=$31, cli_uuid=$32, cli_xml=$33, cli_json=$34, cli_jsonb=$35 "
	" where clicod = $36";

test::entity::Cli_ptr CliDAO::insert(PGconn *con, test::entity::Cli_ptr cli) {
	Param_list pl = to_param_list (cli);
	char **pv = to_param_values(pl);

	PGresult * result = PQexecParams(con, insert_query, (int)pl.size(), NULL, pv, NULL, NULL, 0);
	if (is_error(result)) {
		throw std::runtime_error(PQresultErrorMessage(result));
	}

	free_param_values(pv, pl.size());
	PQclear(result);
	return cli;
}

test::entity::Cli_ptr CliDAO::read(PGconn * con, int clicod) {
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

	Param_list pl;
	pl.push_back(to_param(clicod));
	char **pv = to_param_values(pl);

	PGresult * result = PQexecParams(con, remove_query, (int)pl.size(), NULL, pv, NULL, NULL, 0);
	if (is_error(result)) {
		throw std::runtime_error(PQresultErrorMessage(result));
	}
	retval = (int)strtol(PQcmdTuples(result), NULL, 0);

	free_param_values(pv, pl.size());
	PQclear(result);
	return retval;
}

int CliDAO::update(PGconn *con, test::entity::Cli_ptr cli) {
	int retval;

	Param_list pl = to_param_list(cli);
	pl.push_back(to_param(cli->clicod));
	char **pv = to_param_values(pl);

	PGresult * result = PQexecParams(con, update_query, (int)pl.size(), NULL, pv, NULL, NULL, 0);
	if (is_error(result)) {
		throw std::runtime_error(PQresultErrorMessage(result));
	}
	retval = (int)strtol(PQcmdTuples(result), NULL, 0);

	free_param_values(pv, pl.size());
	PQclear(result);
	return retval;
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
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_integer.reset();
	}
	else {
		cli->cli_integer = std::make_shared<int>(std::atoi(PQgetvalue(result, row_number, index)));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_bigint.reset();
	}
	else {
		cli->cli_bigint = std::make_shared<long>(std::atoi(PQgetvalue(result, row_number, index)));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_numeric.reset();
	}
	else {
		cli->cli_numeric = std::make_shared<double>(std::atof(PQgetvalue(result, row_number, index)));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_numeric_134.reset();
	}
	else {
		cli->cli_numeric_134 = std::make_shared<double>(std::atof(PQgetvalue(result, row_number, index)));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_real.reset();
	}
	else {
		cli->cli_real= std::make_shared<double>(std::atof(PQgetvalue(result, row_number, index)));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_double.reset();
	}
	else {
		cli->cli_double = std::make_shared<double>(std::atof(PQgetvalue(result, row_number, index)));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_timestamp1.reset();
	}
	else {
		cli->cli_timestamp1 = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_timestamp2.reset();
	}
	else {
		cli->cli_timestamp2 = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_date.reset();
	}
	else {
		cli->cli_date = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_time1.reset();
	}
	else {
		cli->cli_time1 = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_time2.reset();
	}
	else {
		cli->cli_time2 = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;

	if (PQgetisnull(result, row_number, index)) {
		cli->cli_interval.reset();
	}
	else {
		cli->cli_interval = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_boolean.reset();
	}
	else {
		cli->cli_boolean = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_char100.reset();
	}
	else {
		cli->cli_char100 = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_text.reset();
	}
	else {
		cli->cli_text = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_point.reset();
	}
	else {
		cli->cli_point = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_line.reset();
	}
	else {
		cli->cli_line = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_lseg.reset();
	}
	else {
		cli->cli_lseg = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_box.reset();
	}
	else {
		cli->cli_box = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_path.reset();
	}
	else {
		cli->cli_path = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_polygon.reset();
	}
	else {
		cli->cli_polygon = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_circle.reset();
	}
	else {
		cli->cli_circle = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_cidr.reset();
	}
	else {
		cli->cli_cidr = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_inet.reset();
	}
	else {
		cli->cli_inet = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_macaddr.reset();
	}
	else {
		cli->cli_macaddr = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_macaddr8.reset();
	}
	else {
		cli->cli_macaddr8 = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_bit10.reset();
	}
	else {
		cli->cli_bit10 = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_bitv10.reset();
	}
	else {
		cli->cli_bitv10 = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_uuid.reset();
	}
	else {
		cli->cli_uuid = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_xml.reset();
	}
	else {
		cli->cli_xml = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_json.reset();
	}
	else {
		cli->cli_json = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	if (PQgetisnull(result, row_number, index)) {
		cli->cli_jsonb.reset();
	}
	else {
		cli->cli_jsonb = std::make_shared<std::string>(PQgetvalue(result, row_number, index));
	}
	index++;
	return cli;
}

Param_list CliDAO::to_param_list(const test::entity::Cli_ptr & cli) {
	Param_list pl;
	pl.push_back(to_param(cli->clicod));
	pl.push_back(to_param(cli->cliraz));
	pl.push_back(to_param(cli->cli_smallint));
	pl.push_back(to_param(cli->cli_integer));
	pl.push_back(to_param(cli->cli_bigint));
	pl.push_back(to_param(cli->cli_numeric));
	pl.push_back(to_param(cli->cli_numeric_134));
	pl.push_back(to_param(cli->cli_real));
	pl.push_back(to_param(cli->cli_double));
	pl.push_back(to_param(cli->cli_timestamp1));
	pl.push_back(to_param(cli->cli_timestamp2));
	pl.push_back(to_param(cli->cli_date));
	pl.push_back(to_param(cli->cli_time1));
	pl.push_back(to_param(cli->cli_time2));
	pl.push_back(to_param(cli->cli_interval));
	pl.push_back(to_param(cli->cli_boolean));
	pl.push_back(to_param(cli->cli_char100));
	pl.push_back(to_param(cli->cli_text));
	pl.push_back(to_param(cli->cli_point));
	pl.push_back(to_param(cli->cli_line));
	pl.push_back(to_param(cli->cli_lseg));
	pl.push_back(to_param(cli->cli_box));
	pl.push_back(to_param(cli->cli_path));
	pl.push_back(to_param(cli->cli_polygon));
	pl.push_back(to_param(cli->cli_circle));
	pl.push_back(to_param(cli->cli_cidr));
	pl.push_back(to_param(cli->cli_inet));
	pl.push_back(to_param(cli->cli_macaddr));
	pl.push_back(to_param(cli->cli_macaddr8));
	pl.push_back(to_param(cli->cli_bit10));
	pl.push_back(to_param(cli->cli_bitv10));
	pl.push_back(to_param(cli->cli_uuid));
	pl.push_back(to_param(cli->cli_xml));
	pl.push_back(to_param(cli->cli_json));
	pl.push_back(to_param(cli->cli_jsonb));
	return pl;
}