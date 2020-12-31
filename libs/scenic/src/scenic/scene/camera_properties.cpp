//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/coordinate_system/object.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/scenic/scene/camera_properties.hpp>


sge::scenic::scene::camera_properties::camera_properties(
	sge::camera::coordinate_system::object const _coordinate_system,
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
