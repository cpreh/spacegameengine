//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/array_or_object.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/variant/comparison.hpp>
#include <fcppt/variant/get_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::json::start::start(
	sge::parse::json::array_or_object &&_variant
)
:
	variant(
		std::move(
			_variant
		)
	)
{
}

sge::parse::json::array &
sge::parse::json::start::array()
{
	return
		fcppt::variant::get_exn<
			sge::parse::json::array
		>(
			variant
		);
}

sge::parse::json::array const &
sge::parse::json::start::array() const
{
	return
		fcppt::variant::get_exn<
			sge::parse::json::array
		>(
			variant
		);
}

sge::parse::json::object &
sge::parse::json::start::object()
{
	return
		fcppt::variant::get_exn<
			sge::parse::json::object
		>(
			variant
		);
}

sge::parse::json::object const &
sge::parse::json::start::object() const
{
	return
		fcppt::variant::get_exn<
			sge::parse::json::object
		>(
			variant
		);
}

bool
sge::parse::json::operator==(
	sge::parse::json::start const &_left,
	sge::parse::json::start const &_right
)
{
	return
		_left.variant
		==
		_right.variant;
}
