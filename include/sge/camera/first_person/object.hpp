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


#ifndef SGE_CAMERA_FIRST_PERSON_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_OBJECT_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/has_activation.hpp>
#include <sge/camera/has_mutable_coordinate_system.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/is_active.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix_fwd.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/first_person/mouse_speed_multiplier.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/parameters_fwd.hpp>
#include <sge/camera/first_person/action/mapping.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace camera
{
namespace first_person
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
:
	public virtual sge::camera::base,
	public sge::camera::has_activation,
	public sge::camera::is_dynamic,
	public sge::camera::has_mutable_projection,
	public sge::camera::has_mutable_coordinate_system
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	explicit
	object(
		sge::camera::first_person::parameters const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::object const
	coordinate_system() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update_coordinate_system(
		sge::camera::coordinate_system::object const &
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::projection_matrix const
	projection_matrix() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update_projection_matrix(
		sge::camera::projection_matrix const &
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::is_active const
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
	~object()
	override;
private:
	fcppt::signal::auto_connection const keyboard_connection_;

	fcppt::signal::auto_connection const mouse_axis_connection_;

	sge::camera::first_person::action::mapping action_mapping_;

	sge::camera::first_person::movement_speed movement_speed_;

	sge::camera::first_person::mouse_speed_multiplier mouse_speed_multiplier_;

	sge::camera::is_active is_active_;

	sge::renderer::vector3 directions_;

	sge::camera::coordinate_system::object coordinate_system_;

	sge::camera::optional_projection_matrix projection_matrix_;

	bool left_pressed_, right_pressed_;

	bool up_pressed_, down_pressed_;

	bool forward_pressed_, backward_pressed_;

	void
	key_callback(
		sge::input::keyboard::key_event const &
	);

	void
	mouse_axis_callback(
		sge::input::mouse::axis_event const &
	);

	void
	rotate_on_x(
		sge::renderer::scalar
	);

	void
	rotate_on_y(
		sge::renderer::scalar
	);
};

}
}
}

#endif
