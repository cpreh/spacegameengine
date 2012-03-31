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


#ifndef SGE_CAMERA_FIRST_PERSON_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_OBJECT_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/base.hpp>
#include <sge/camera/has_activation.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/first_person/is_active.hpp>
#include <sge/camera/first_person/mouse_speed_multiplier.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/parameters_fwd.hpp>
#include <sge/camera/first_person/action/mapping.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace camera
{
namespace first_person
{
class SGE_CLASS_SYMBOL object
:
	public sge::camera::base,
	public sge::camera::has_activation,
	public sge::camera::is_dynamic,
	public sge::camera::has_mutable_projection
{
public:
	SGE_CAMERA_SYMBOL
	explicit
	object(
		first_person::parameters const &);

	/* override */
	SGE_CAMERA_SYMBOL
	camera::coordinate_system::object const
	coordinate_system() const;

	/* override */
	SGE_CAMERA_SYMBOL
	camera::projection_matrix const
	projection_matrix() const;

	/* override */
	SGE_CAMERA_SYMBOL
	void
	projection_matrix(
		sge::camera::projection_matrix const &);

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
	~object();
private:
	fcppt::signal::scoped_connection keyboard_connection_;
	fcppt::signal::scoped_connection mouse_axis_connection_;
	first_person::action::mapping action_mapping_;
	first_person::movement_speed movement_speed_;
	first_person::mouse_speed_multiplier mouse_speed_multiplier_;
	first_person::is_active is_active_;
	sge::renderer::vector3 directions_;
	camera::coordinate_system::object coordinate_system_;
	camera::optional_projection_matrix projection_matrix_;
	bool left_pressed_,right_pressed_;
	bool up_pressed_,down_pressed_;
	bool forward_pressed_,backward_pressed_;

	void
	key_callback(
		sge::input::keyboard::key_event const &);

	void
	mouse_axis_callback(
		sge::input::mouse::axis_event const &);

	void
	rotate_on_x(
		sge::renderer::scalar);

	void
	rotate_on_y(
		sge::renderer::scalar);
};
}
}
}

#endif
