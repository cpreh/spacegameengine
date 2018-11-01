/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/camera/coordinate_system/object.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/scenic/scene/camera_properties.hpp>


sge::scenic::scene::camera_properties::camera_properties(
	sge::camera::coordinate_system::object const &_coordinate_system,
	sge::renderer::projection::fov const &_fov,
	sge::renderer::projection::near const &_near,
	sge::renderer::projection::far const &_far
)
:
	coordinate_system_(
		_coordinate_system
	),
	fov_(
		_fov
	),
	near_(
		_near
	),
	far_(
		_far
	)
{
}

sge::camera::coordinate_system::object const &
sge::scenic::scene::camera_properties::coordinate_system() const
{
		return
			coordinate_system_;
}

sge::renderer::projection::fov const &
sge::scenic::scene::camera_properties::fov() const
{
		return
			fov_;
}

sge::renderer::projection::near const &
sge::scenic::scene::camera_properties::near() const
{
		return
			near_;
}

sge::renderer::projection::far const &
sge::scenic::scene::camera_properties::far() const
{
		return
			far_;
}
