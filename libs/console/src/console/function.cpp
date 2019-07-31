//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/console/function.hpp>
#include <sge/console/long_description.hpp>
#include <sge/console/short_description.hpp>
#include <sge/console/signal.hpp>


sge::console::function::function(
	sge::console::short_description const &_short_description,
	sge::console::long_description const &_long_description
)
:
	signal_(),
	short_description_(
		_short_description
	),
	long_description_(
		_long_description
	)
{
}

sge::console::function::function(
	function &&
) = default;


sge::console::function &
sge::console::function::operator=(
	function &&
) = default;

sge::console::function::~function()
{
}

sge::console::signal &
sge::console::function::signal()
{
	return
		signal_;
}

sge::console::short_description const &
sge::console::function::short_description() const
{
	return
		short_description_;
}

sge::console::long_description const &
sge::console::function::long_description() const
{
	return
		long_description_;
}
