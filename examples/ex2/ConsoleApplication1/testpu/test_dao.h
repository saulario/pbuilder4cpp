#ifndef TEST_DAO_H
#define TEST_DAO_H

#include <memory>

#include "libpq-fe.h"
#include "test_entity.h"

namespace test {
	namespace dao {

		class CliDAO {
		public:
			static test::entity::Cli_ptr read(PGconn *, int);
		 };

		class TestDAO {
		public:
			TestDAO();
			~TestDAO();

			static test::entity::Test_ptr insert(PGconn *, test::entity::Test_ptr);
			static test::entity::Test_ptr read(PGconn *, long);
			static test::entity::Test_list query(PGconn *);
			static void remove(PGconn *, long);
			static test::entity::Test_ptr update(PGconn *, test::entity::Test_ptr);


		};

	}
}

#endif