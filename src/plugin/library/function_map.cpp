/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/plugin/library/exception.hpp>
#include <sge/plugin/library/function_map.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>


sge::plugin::library::function_map::function_map(
	container const &_functions
)
:
	functions_(_functions)
{
}

sge::plugin::library::function_base
sge::plugin::library::function_map::function(
	library::symbol_string const &_name
) const
{
	container::const_iterator const it(
		functions_.find(
			_name
		)
	);

	// this should not happen
	if(
		it == functions_.end()
	)
		throw sge::plugin::library::exception(
			FCPPT_TEXT("Missing function \"")
			+
			fcppt::from_std_string(
				_name
			)
			+
			FCPPT_TEXT("\" in a library!")
		);

	return it->second;
}

sge::plugin::library::function_map::container const &
sge::plugin::library::function_map::get() const
{
	return functions_;
}
