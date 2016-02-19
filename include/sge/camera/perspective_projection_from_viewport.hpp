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


#ifndef SGE_CAMERA_PERSPECTIVE_PROJECTION_FROM_VIEWPORT_HPP_INCLUDED
#define SGE_CAMERA_PERSPECTIVE_PROJECTION_FROM_VIEWPORT_HPP_INCLUDED

#include <sge/camera/has_mutable_projection_fwd.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace camera
{

class perspective_projection_from_viewport
{
	FCPPT_NONCOPYABLE(
		perspective_projection_from_viewport
	);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	perspective_projection_from_viewport(
		sge::camera::has_mutable_projection &,
		sge::viewport::manager &,
		sge::renderer::projection::near,
		sge::renderer::projection::far,
		sge::renderer::projection::fov
	);

	SGE_CAMERA_DETAIL_SYMBOL
	~perspective_projection_from_viewport();
private:
	sge::camera::has_mutable_projection &camera_;

	sge::renderer::projection::near const near_;

	sge::renderer::projection::far const far_;

	sge::renderer::projection::fov const fov_;

	fcppt::signal::auto_connection const viewport_callback_connection_;

	void
	viewport_callback(
		sge::renderer::target::viewport const &
	);
};

}
}

#endif
