//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_FILE_RESULT_FWD_HPP_INCLUDED
#define SGE_PARSE_JSON_FILE_RESULT_FWD_HPP_INCLUDED

#include <sge/parse/file_result_fwd.hpp>
#include <sge/parse/json/start_fwd.hpp>


namespace sge::parse::json
{

using
file_result
=
sge::parse::file_result<
	char,
	sge::parse::json::start
>;

}

#endif
