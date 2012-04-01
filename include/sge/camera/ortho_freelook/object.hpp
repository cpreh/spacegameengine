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
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/ortho_freelook/optional_projection_rectangle.hpp>
#include <sge/camera/ortho_freelook/pan_speed.hpp>
#include <sge/camera/ortho_freelook/parameters_fwd.hpp>
#include <sge/camera/ortho_freelook/zoom_speed.hpp>
#include <sge/camera/ortho_freelook/action/mapping.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{
/**
Note to self: The zoom speed measures how much of the original "viewable
rectangle" is visible after a second of zooming. A zoom speed of 0.1 means 90%
of the screen is visible after a second of zooming.

The panning speed is the amount of panning (measured in percent of the current
rectangle) that is done when the mouse moves by "one".
*/
class SGE_CLASS_SYMBOL object
:
	public camera::base,
	public camera::is_dynamic,
	public camera::has_activation
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_CAMERA_SYMBOL
	explicit
	object(
		ortho_freelook::parameters const &);

	SGE_CAMERA_SYMBOL
	void
	zoom_speed(
		ortho_freelook::zoom_speed const &);

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

	/* override */
	SGE_CAMERA_SYMBOL
	void
	update(
		camera::update_duration const &);

	SGE_CAMERA_SYMBOL
	void
	projection_rectangle(
		renderer::projection::rect const &);

	SGE_CAMERA_SYMBOL
	~object();
private:
	fcppt::signal::scoped_connection mouse_axis_connection_;
	fcppt::signal::scoped_connection keyboard_key_connection_;
	ortho_freelook::action::mapping action_mapping_;
	ortho_freelook::optional_projection_rectangle current_projection_rectangle_;
	ortho_freelook::zoom_speed zoom_speed_;
	ortho_freelook::pan_speed pan_speed_;
	renderer::projection::near near_;
	renderer::projection::far far_;
	bool is_active_;
	bool zoom_in_pressed_;
	bool zoom_out_pressed_;
	bool pan_pressed_;

	void
	mouse_axis_callback(
		sge::input::mouse::axis_event const &);

	void
	key_callback(
		sge::input::keyboard::key_event const &);
};
}
}
}

#endif

