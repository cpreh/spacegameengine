/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CAMERA_FIRST_PERSON_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_PARAMETERS_HPP_INCLUDED

#include <sge/camera/is_active.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/first_person/mouse_speed_multiplier.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/action/mapping.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/matrix/object_impl.hpp>


namespace sge
{
namespace camera
{
namespace first_person
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_CAMERA_SYMBOL
	parameters(
		sge::input::keyboard::device &,
		sge::input::mouse::device &,
		sge::camera::is_active const &,
		sge::camera::first_person::movement_speed const &,
		camera::coordinate_system::object const &);

	SGE_CAMERA_SYMBOL
	sge::input::keyboard::device &
	keyboard() const;

	SGE_CAMERA_SYMBOL
	sge::input::mouse::device &
	mouse() const;

	SGE_CAMERA_SYMBOL
	sge::camera::is_active const &
	is_active() const;

	SGE_CAMERA_SYMBOL
	parameters &
	action_mapping(
		sge::camera::first_person::action::mapping const &);

	SGE_CAMERA_SYMBOL
	sge::camera::first_person::action::mapping const &
	action_mapping() const;

	SGE_CAMERA_SYMBOL
	sge::camera::first_person::movement_speed const &
	movement_speed() const;

	SGE_CAMERA_SYMBOL
	sge::camera::coordinate_system::object const &
	coordinate_system() const;

	SGE_CAMERA_SYMBOL
	parameters &
	mouse_speed_multiplier(
		sge::camera::first_person::mouse_speed_multiplier const &);

	SGE_CAMERA_SYMBOL
	sge::camera::first_person::mouse_speed_multiplier const &
	mouse_speed_multiplier() const;

	// Projection is optional on construction, since we might know it only
	// after we get a viewport.
	SGE_CAMERA_SYMBOL
	parameters &
	projection(
		sge::camera::projection_matrix const &);

	SGE_CAMERA_SYMBOL
	sge::camera::optional_projection_matrix const &
	projection_matrix() const;
private:
	sge::input::keyboard::device &keyboard_;
	sge::input::mouse::device &mouse_;
	sge::camera::is_active is_active_;
	action::mapping action_mapping_;
	sge::camera::first_person::movement_speed movement_speed_;
	sge::camera::coordinate_system::object coordinate_system_;
	sge::camera::first_person::mouse_speed_multiplier mouse_speed_multiplier_;
	sge::camera::optional_projection_matrix projection_matrix_;
};
}
}
}

#endif

