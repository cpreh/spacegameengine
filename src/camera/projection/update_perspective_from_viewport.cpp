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


#include <sge/camera/projection/update_perspective_from_viewport.hpp>
#include <sge/camera/projection/perspective.hpp>
#include <sge/camera/object.hpp>
#include <sge/renderer/active_target.hpp>
#include <sge/renderer/aspect_from_viewport.hpp>
#include <sge/renderer/target_base.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>

void
sge::camera::projection::update_perspective_from_viewport(
	sge::renderer::device &_device,
	camera::object &_object,
	renderer::projection::fov const _fov,
	renderer::projection::near const _near,
	renderer::projection::far const _far
)
{
	_object.projection_object(
		projection::perspective(
			sge::renderer::projection::aspect(
				sge::renderer::aspect_from_viewport(
					sge::renderer::active_target(
						_device
					).viewport()
				)
			),
			_fov,
			_near,
			_far
		)
	);
}
