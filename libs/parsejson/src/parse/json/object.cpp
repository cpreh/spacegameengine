//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/recursive_comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::json::object::object(
	sge::parse::json::member_map &&_members
)
:
	members(
		std::move(
			_members
		)
	)
{
}

bool
sge::parse::json::operator==(
	sge::parse::json::object const &_left,
	sge::parse::json::object const &_right
)
{
	return
		_left.members
		==
		_right.members;
}
