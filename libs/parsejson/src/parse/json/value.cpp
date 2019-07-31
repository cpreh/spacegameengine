//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/json/value.hpp>
#include <sge/parse/json/value_variant.hpp>
#include <fcppt/variant/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::json::value::value(
	sge::parse::json::value_variant &&_impl
)
:
	impl{
		std::move(
			_impl
		)
	}
{
}

sge::parse::json::value_variant const &
sge::parse::json::value::get() const
{
	return
		impl;
}

sge::parse::json::value_variant &
sge::parse::json::value::get()
{
	return
		impl;
}

bool
sge::parse::json::operator==(
	sge::parse::json::value const &_left,
	sge::parse::json::value const &_right
)
{
	return
		_left.get()
		==
		_right.get();
}
