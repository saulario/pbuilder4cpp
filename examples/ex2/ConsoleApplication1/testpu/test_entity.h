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
		};

		typedef std::shared_ptr<Cli> Cli_ptr;
		typedef std::list<Cli_ptr> Cli_list;

	}
}

#endif 
