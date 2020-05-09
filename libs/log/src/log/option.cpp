//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/log/option.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::log::option::option(
	fcppt::log::location &&_location,
	fcppt::log::level const _level
)
:
	location_(
		std::move(
			_location
		)
	),
	level_(
		_level
	)
{
}

fcppt::log::location const &
sge::log::option::location() const
{
	return
		location_;
}

fcppt::log::level
sge::log::option::level() const
{
	return
		level_;
}
