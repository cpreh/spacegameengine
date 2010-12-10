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


#include <sge/window/create_simple_from_awl.hpp>
#include <sge/window/simple_parameters.hpp>
#include <awl/window/parameters.hpp>
#include <awl/system/object.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

awl::window::instance_ptr const
sge::window::create_simple_from_awl(
	awl::system::object_ptr const _system,
	sge::window::simple_parameters const &_param
)
{
	return
		_system->create(
			awl::window::parameters()
			.title(
				_param.title()
			)
			.class_name(
				_param.class_name()
			)
			.size(
				fcppt::math::dim::structure_cast<
					awl::window::dim
				>(
					_param.dim()
				)
			)
		);
}
