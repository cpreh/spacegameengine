/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/camera/base.hpp>
#include <sge/camera/has_activation.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/ortho_freelook/optional_projection_rectangle.hpp>
#include <sge/camera/ortho_freelook/pan_speed.hpp>
#include <sge/camera/ortho_freelook/parameters_fwd.hpp>
#include <sge/camera/ortho_freelook/zoom_speed.hpp>
#include <sge/camera/ortho_freelook/action/mapping.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/signal/auto_connection.hpp>


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
class SGE_CORE_DETAIL_CLASS_SYMBOL object
:
	public virtual sge::camera::base,
	public sge::camera::is_dynamic,
	public sge::camera::has_activation
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	explicit
	object(
		sge::camera::ortho_freelook::parameters const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	void
	zoom_speed(
		sge::camera::ortho_freelook::zoom_speed const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::object
	coordinate_system() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::projection_matrix
	projection_matrix() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::is_active
	is_active() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	is_active(
		sge::camera::is_active
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update(
		sge::camera::update_duration
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	projection_rectangle(
		sge::renderer::projection::rect const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	~object()
	override;
private:
	fcppt::signal::auto_connection const mouse_axis_connection_;

	fcppt::signal::auto_connection const keyboard_key_connection_;

	sge::camera::ortho_freelook::action::mapping action_mapping_;

	sge::camera::ortho_freelook::optional_projection_rectangle current_projection_rectangle_;

	sge::camera::ortho_freelook::zoom_speed zoom_speed_;

	sge::camera::ortho_freelook::pan_speed pan_speed_;

	sge::renderer::projection::near near_;

	sge::renderer::projection::far far_;

	sge::camera::is_active is_active_;

	bool zoom_in_pressed_;

	bool zoom_out_pressed_;

	bool pan_pressed_;

	void
	mouse_axis_callback(
		sge::input::mouse::axis_event const &
	);

	void
	key_callback(
		sge::input::keyboard::key_event const &
	);
};

}
}
}

#endif

