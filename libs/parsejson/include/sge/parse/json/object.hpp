//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_OBJECT_HPP_INCLUDED
#define SGE_PARSE_JSON_OBJECT_HPP_INCLUDED

#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/detail/symbol.hpp>


namespace sge
{
namespace parse
{
namespace json
{

struct object
{
	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	object(
		sge::parse::json::member_map &&
	);

	sge::parse::json::member_map members;
};

SGE_PARSE_JSON_DETAIL_SYMBOL
bool
operator==(
	sge::parse::json::object const &,
	sge::parse::json::object const &
);

}
}
}

#endif
