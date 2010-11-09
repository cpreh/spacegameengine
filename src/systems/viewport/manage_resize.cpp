/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "resize_manager.hpp"
#include <sge/systems/viewport/manage_resize.hpp>
#include <sge/systems/viewport/manager.hpp>
#include <sge/systems/viewport/manager_unique_ptr.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>

sge::systems::viewport::factory const
sge::systems::viewport::manage_resize()
{
	return
		boost::phoenix::construct<
			viewport::manager_unique_ptr
		>(
			boost::phoenix::new_<
				viewport::resize_manager
			>(
				boost::phoenix::arg_names::arg1
			)
		);
}
