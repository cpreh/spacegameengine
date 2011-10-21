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


#include <sge/window/create_simple_from_awl.hpp>
#include <sge/window/to_awl_parameters.hpp>
#include <awl/system/object.hpp>
#include <awl/window/instance.hpp>
#include <awl/window/parameters.hpp>


awl::window::instance_shared_ptr const
sge::window::create_simple_from_awl(
	awl::system::object &_system,
	sge::window::simple_parameters const &_param
)
{
	return
		awl::window::instance_shared_ptr(
			_system.create(
				sge::window::to_awl_parameters(
					_param
				)
			)
		);
}
