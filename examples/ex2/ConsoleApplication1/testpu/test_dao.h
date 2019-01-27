#ifndef TEST_DAO_H
#define TEST_DAO_H

#include <list>
#include <memory>

#include "libpq-fe.h"
#include "test_entity.h"

namespace test {
	namespace dao {

		bool is_error(PGresult *);

		class Parameter {
		public:

			Parameter() : buffer(""), null_param(true) {}

			Parameter(const std::string & p_buffer, bool is_null = false) :
				buffer(p_buffer), null_param(is_null) {
			}

			const char * c_str(void) {
				return (is_null() ? NULL : buffer.c_str());
			}

			inline bool is_null(void) { return null_param; }
			inline bool not_null(void) { return !is_null(); }

		private:
			bool null_param;
			std::string buffer;
		};

		typedef std::list<Parameter> Param_list;
		char **to_param_values(const Param_list &);
		void free_param_values(char **, size_t);

		template <typename P> Parameter to_param(P p);
		template <typename P> Parameter to_param(std::shared_ptr<P> p);

		class CliDAO {
		public:
			static test::entity::Cli_ptr insert(PGconn *, test::entity::Cli_ptr);
			static test::entity::Cli_ptr read(PGconn *, int);
			static test::entity::Cli_list query(PGconn *, const std::string &, const Param_list &);
			static int remove(PGconn *, int);
			static test::entity::Cli_ptr update(PGconn *, test::entity::Cli_ptr);

		private:
			static test::entity::Cli_ptr load_columns(PGresult *, int = 0);
			static const char * insert_query;
			static const char * read_query;
			static const char * remove_query;
			static const char * update_query;
		 };

	}
}

#endif