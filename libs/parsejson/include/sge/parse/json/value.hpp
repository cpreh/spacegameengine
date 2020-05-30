//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_VALUE_HPP_INCLUDED
#define SGE_PARSE_JSON_VALUE_HPP_INCLUDED

#include <sge/parse/json/value_fwd.hpp>
#include <sge/parse/json/value_variant.hpp>
#include <sge/parse/json/detail/symbol.hpp>


namespace sge
{
namespace parse
{
namespace json
{

struct value
{
	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	value(
		sge::parse::json::value_variant &&
	);

	[[nodiscard]]
	SGE_PARSE_JSON_DETAIL_SYMBOL
	sge::parse::json::value_variant const &
	get() const;

	[[nodiscard]]
	SGE_PARSE_JSON_DETAIL_SYMBOL
	sge::parse::json::value_variant &
	get();

	sge::parse::json::value_variant impl; // NOLINT(misc-non-private-member-variables-in-classes)
};

SGE_PARSE_JSON_DETAIL_SYMBOL
bool
operator==(
	sge::parse::json::value const &,
	sge::parse::json::value const &
);

}
}
}

#endif
