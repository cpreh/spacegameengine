//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_PATH_TO_STRING_HPP_INCLUDED
#define SGE_PARSE_JSON_PATH_TO_STRING_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/path_fwd.hpp>
#include <sge/parse/json/detail/symbol.hpp>


namespace sge::parse::json
{

SGE_PARSE_JSON_DETAIL_SYMBOL
sge::charconv::utf8_string
path_to_string(
	sge::parse::json::path const &
);

}

#endif
