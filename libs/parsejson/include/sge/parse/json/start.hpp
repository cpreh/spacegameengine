//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_START_HPP_INCLUDED
#define SGE_PARSE_JSON_START_HPP_INCLUDED

#include <sge/parse/json/array_fwd.hpp>
#include <sge/parse/json/array_or_object.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/start_fwd.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/symbol.hpp>


namespace sge::parse::json
{

struct start
{
	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	start(
		sge::parse::json::array_or_object &&
	);

	[[nodiscard]]
	SGE_PARSE_JSON_DETAIL_SYMBOL
	sge::parse::json::array &
	array();

	[[nodiscard]]
	SGE_PARSE_JSON_DETAIL_SYMBOL
	sge::parse::json::array const &
	array() const;

	[[nodiscard]]
	SGE_PARSE_JSON_DETAIL_SYMBOL
	sge::parse::json::object &
	object();

	[[nodiscard]]
	SGE_PARSE_JSON_DETAIL_SYMBOL
	sge::parse::json::object const &
	object() const;

	sge::parse::json::array_or_object variant; // NOLINT(misc-non-private-member-variables-in-classes)
};

SGE_PARSE_JSON_DETAIL_SYMBOL
bool
operator==(
	sge::parse::json::start const &,
	sge::parse::json::start const &
);

}

#endif
