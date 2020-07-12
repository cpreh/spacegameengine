//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/console/long_description.hpp>
#include <sge/console/short_description.hpp>
#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/font/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::console::callback::parameters::parameters(
	sge::console::callback::function &&_function,
	sge::console::callback::name &&_name
)
:
	function_(
		std::move(
			_function
		)
	),
	name_(
		std::move(
			_name.get()
		)
	),
	short_description_(
		sge::font::string()
	),
	long_description_(
		sge::font::string()
	)
{
}

sge::console::callback::parameters
sge::console::callback::parameters::short_description(
	sge::font::string &&_short_description
) &&
{
	short_description_ =
		sge::console::short_description(
			std::move(
				_short_description
			)
		);

	return
		std::move(
			*this
		);
}

sge::console::callback::parameters
sge::console::callback::parameters::long_description(
	sge::font::string &&_long_description
) &&
{
	long_description_ =
		sge::console::long_description(
			std::move(
				_long_description
			)
		);

	return
		std::move(
			*this
		);
}

sge::console::callback::function &
sge::console::callback::parameters::function()
{
	return
		function_;
}

sge::console::callback::function const &
sge::console::callback::parameters::function() const
{
	return
		function_;
}

sge::font::string &
sge::console::callback::parameters::name()
{
	return
		name_;
}

sge::font::string const &
sge::console::callback::parameters::name() const
{
	return
		name_;
}

sge::console::short_description &
sge::console::callback::parameters::short_description()
{
	return
		short_description_;
}

sge::console::short_description const &
sge::console::callback::parameters::short_description() const
{
	return
		short_description_;
}

sge::console::long_description &
sge::console::callback::parameters::long_description()
{
	return
		long_description_;
}

sge::console::long_description const &
sge::console::callback::parameters::long_description() const
{
	return
		long_description_;
}
