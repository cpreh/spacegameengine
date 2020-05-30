//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_ARRAY_HPP_INCLUDED
#define SGE_PARSE_JSON_ARRAY_HPP_INCLUDED

#include <sge/parse/json/array_fwd.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/detail/symbol.hpp>


namespace sge
{
namespace parse
{
namespace json
{

struct array
{
	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	array(
		sge::parse::json::element_vector &&
	);

	sge::parse::json::element_vector elements; // NOLINT(misc-non-private-member-variables-in-classes)
};

SGE_PARSE_JSON_DETAIL_SYMBOL
bool
operator==(
	sge::parse::json::array const &,
	sge::parse::json::array const &
);

}
}
}

#endif
