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


#ifndef SGE_CAMERA_ORTHO_FREELOOK_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_OBJECT_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/base.hpp>
#include <sge/camera/has_activation.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/ortho_freelook/optional_projection_rectangle.hpp>
#include <sge/camera/ortho_freelook/pan_speed.hpp>
#include <sge/camera/ortho_freelook/parameters_fwd.hpp>
#include <sge/camera/ortho_freelook/zoom_speed.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{
class SGE_CLASS_SYMBOL object
:
	public camera::base,
	public camera::has_activation
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_CAMERA_SYMBOL
	explicit
	object(
		ortho_freelook::parameters const &);

	/* override */
	SGE_CAMERA_SYMBOL
	coordinate_system::object const
	coordinate_system() const;

	/* override */
	SGE_CAMERA_SYMBOL
	camera::projection_matrix const
	projection_matrix() const;

	/* override */
	SGE_CAMERA_SYMBOL
	bool
	is_active() const;

	/* override */
	SGE_CAMERA_SYMBOL
	void
	is_active(
		bool);

	SGE_CAMERA_SYMBOL
	void
	projection_rectangle(
		renderer::projection::rect const &);

	SGE_CAMERA_SYMBOL
	~object();
private:
	ortho_freelook::optional_projection_rectangle base_projection_rectangle_;
	renderer::projection::rect current_projection_rectangle_;
	ortho_freelook::zoom_speed zoom_speed_;
	ortho_freelook::pan_speed pan_speed_;
	renderer::projection::near near_;
	renderer::projection::far far_;
	bool is_active_;

	void
	mouse_axis_callback(
		sge::input::mouse::axis_event const &);
};
}
}
}

#endif

