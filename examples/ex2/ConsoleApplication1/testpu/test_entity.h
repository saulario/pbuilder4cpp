#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H

#include <list>
#include <memory>

namespace test {
	namespace entity {

		// Postgresql	C++
		// smallint, smallserial		short int
		// integer, serial				int	
		// big int, big serial			long int
		//
		// numeric, double				double
		// real							float
		// 

		class Cli {
		public:
			int clicod;
			std::string cliextcod;
			std::string clinom;
			std::string clinif;
			std::string clipcp;
			std::string clipob;
			std::string clitlf;
			std::string clifax;
			std::string clieml;
			std::string clida1;
			std::string clida2;
			std::string clida3;
			std::string clida4;
			std::string climoacod;
			std::string clipaicod;

			std::unique_ptr<std::string> cliestcod;

		};

		typedef std::unique_ptr<Cli> Cli_ptr;
		typedef std::list<Cli_ptr> Cli_list;

		class Test {
		public:
			Test();
			~Test();
		};

		typedef std::unique_ptr<Test> Test_ptr;
		typedef std::list<Test_ptr> Test_list;

	}
}

#endif 
