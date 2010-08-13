/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/state/combine.hpp>
#include <sge/renderer/state/list.hpp>
#include <boost/foreach.hpp>

sge::renderer::state::list const
sge::renderer::state::combine(
	list const &_left,
	list const &_right
)
{
	list result(
		_left
	);

	BOOST_FOREACH(
		any const &rstate,
		_right.values()
	)
		result.overwrite(
			rstate
		);

	return result;
}
