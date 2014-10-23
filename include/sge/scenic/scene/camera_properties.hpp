/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SCENIC_SCENE_CAMERA_PROPERTIES_HPP_INCLUDED
#define SGE_SCENIC_SCENE_CAMERA_PROPERTIES_HPP_INCLUDED

#include <sge/camera/coordinate_system/object.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/scenic/detail/symbol.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
class camera_properties
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	camera_properties(
		sge::camera::coordinate_system::object const &,
		sge::renderer::projection::fov const &,
		sge::renderer::projection::near const &,
		sge::renderer::projection::far const &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::camera::coordinate_system::object const &
	coordinate_system() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::projection::fov const &
	fov() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::projection::near const &
	near() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::projection::far const &
	far() const;

	SGE_SCENIC_DETAIL_SYMBOL
	~camera_properties();
private:
	sge::camera::coordinate_system::object coordinate_system_;
	sge::renderer::projection::fov fov_;
	sge::renderer::projection::near near_;
	sge::renderer::projection::far far_;
};
}
}
}

#endif
