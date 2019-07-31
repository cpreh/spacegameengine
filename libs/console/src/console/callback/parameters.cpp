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


sge::console::callback::parameters::parameters(
	sge::console::callback::function const &_function,
	sge::console::callback::name const &_name
)
:
	function_(
		_function
	),
	name_(
		_name.get()
	),
	short_description_(
		sge::font::string()
	),
	long_description_(
		sge::font::string()
	)
{
}

sge::console::callback::parameters &
sge::console::callback::parameters::short_description(
	sge::font::string const &_short_description
)
{
	short_description_ =
		sge::console::short_description(
			_short_description
		);

	return *this;
}

sge::console::callback::parameters &
sge::console::callback::parameters::long_description(
	sge::font::string const &_long_description
)
{
	long_description_ =
		sge::console::long_description(
			_long_description
		);

	return *this;
}

sge::console::callback::function const &
sge::console::callback::parameters::function() const
{
	return function_;
}

sge::font::string const &
sge::console::callback::parameters::name() const
{
	return name_;
}

sge::console::short_description const &
sge::console::callback::parameters::short_description() const
{
	return short_description_;
}

sge::console::long_description const &
sge::console::callback::parameters::long_description() const
{
	return long_description_;
}
