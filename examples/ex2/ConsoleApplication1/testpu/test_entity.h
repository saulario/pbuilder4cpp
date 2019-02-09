#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H

#include <list>
#include <memory>

namespace test {
	namespace entity {

		class Cli {
		public:
			int clicod;
			std::shared_ptr<std::string> cliraz;
			std::shared_ptr<short> cli_smallint;
			std::shared_ptr<int> cli_integer;
			std::shared_ptr<long> cli_bigint;
			std::shared_ptr<double> cli_numeric;
			std::shared_ptr<double> cli_numeric_134;
			std::shared_ptr<double> cli_real;
			std::shared_ptr<double> cli_double;
			std::shared_ptr<std::string> cli_timestamp1;
			std::shared_ptr<std::string> cli_timestamp2;
			std::shared_ptr<std::string> cli_date;
			std::shared_ptr<std::string> cli_time1;
			std::shared_ptr<std::string> cli_time2;
			std::shared_ptr<std::string> cli_interval;
			std::shared_ptr<bool> cli_boolean;
			std::shared_ptr<std::string> cli_char100;
			std::shared_ptr<std::string> cli_text;
			std::shared_ptr<std::string> cli_point;
			std::shared_ptr<std::string> cli_line;
			std::shared_ptr<std::string> cli_lseg;
			std::shared_ptr<std::string> cli_box;
			std::shared_ptr<std::string> cli_path;
			std::shared_ptr<std::string> cli_polygon;
			std::shared_ptr<std::string> cli_circle;
			std::shared_ptr<std::string> cli_cidr;
			std::shared_ptr<std::string> cli_inet;
			std::shared_ptr<std::string> cli_macaddr;
			std::shared_ptr<std::string> cli_macaddr8;
			std::shared_ptr<std::string> cli_bit10;
			std::shared_ptr<std::string> cli_bitv10;
			std::shared_ptr<std::string> cli_uuid;
			std::shared_ptr<std::string> cli_xml;
			std::shared_ptr<std::string> cli_json;
			std::shared_ptr<std::string> cli_jsonb;
		};

		typedef std::shared_ptr<Cli> Cli_ptr;
		typedef std::list<Cli_ptr> Cli_list;

	}
}

#endif 
