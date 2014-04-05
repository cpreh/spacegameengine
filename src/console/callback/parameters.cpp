/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
