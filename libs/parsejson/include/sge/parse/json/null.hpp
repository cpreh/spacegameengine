//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_NULL_HPP_INCLUDED
#define SGE_PARSE_JSON_NULL_HPP_INCLUDED

#include <sge/parse/json/null_fwd.hpp>
#include <sge/parse/json/detail/symbol.hpp>


namespace sge::parse::json
{

struct null
{
};

SGE_PARSE_JSON_DETAIL_SYMBOL
bool
operator==(
	sge::parse::json::null const &,
	sge::parse::json::null const &
);

}

#endif
