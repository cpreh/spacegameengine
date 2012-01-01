/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/camera/identity_gizmo.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


sge::camera::gizmo_type
sge::camera::identity_gizmo()
{
	return
		gizmo_type()
			.position(
				sge::renderer::vector3::null())
			.right(
				sge::renderer::vector3(1,0,0))
			.up(
				sge::renderer::vector3(0,1,0))
			.forward(
				sge::renderer::vector3(0,0,1));
}
