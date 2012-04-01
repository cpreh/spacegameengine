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


#ifndef SGE_CAMERA_SPHERICAL_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_PARAMETERS_HPP_INCLUDED

#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/spherical/acceleration_factor.hpp>
#include <sge/camera/spherical/damping_factor.hpp>
#include <sge/camera/spherical/is_active.hpp>
#include <sge/camera/spherical/maximum_radius.hpp>
#include <sge/camera/spherical/minimum_radius.hpp>
#include <sge/camera/spherical/movement_speed.hpp>
#include <sge/camera/spherical/origin.hpp>
#include <sge/camera/spherical/action/mapping.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace sge
{
namespace camera
{
namespace spherical
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_CAMERA_SYMBOL
	explicit
	parameters(
		input::keyboard::device &,
		spherical::is_active const &,
		spherical::coordinate_system::object const &,
		spherical::action::mapping const &);

	SGE_CAMERA_SYMBOL
	input::keyboard::device &
	keyboard() const;

	SGE_CAMERA_SYMBOL
	spherical::is_active const &
	is_active() const;

	SGE_CAMERA_SYMBOL
	spherical::coordinate_system::object const &
	coordinate_system() const;

	SGE_CAMERA_SYMBOL
	spherical::action::mapping const &
	action_mapping() const;

	SGE_CAMERA_SYMBOL
	parameters &
	movement_speed(
		spherical::movement_speed const &);

	SGE_CAMERA_SYMBOL
	spherical::movement_speed const &
	movement_speed() const;

	SGE_CAMERA_SYMBOL
	parameters &
	origin(
		spherical::origin const &);

	SGE_CAMERA_SYMBOL
	spherical::origin const &
	origin() const;

	SGE_CAMERA_SYMBOL
	parameters &
	minimum_radius(
		spherical::minimum_radius const &);

	SGE_CAMERA_SYMBOL
	spherical::minimum_radius const &
	minimum_radius() const;

	SGE_CAMERA_SYMBOL
	parameters &
	maximum_radius(
		spherical::maximum_radius const &);

	SGE_CAMERA_SYMBOL
	spherical::maximum_radius const &
	maximum_radius() const;

	SGE_CAMERA_SYMBOL
	parameters &
	acceleration_factor(
		spherical::acceleration_factor const &);

	SGE_CAMERA_SYMBOL
	spherical::acceleration_factor const &
	acceleration_factor() const;

	SGE_CAMERA_SYMBOL
	parameters &
	damping_factor(
		spherical::damping_factor const &);

	SGE_CAMERA_SYMBOL
	spherical::damping_factor const &
	damping_factor() const;

	// Projection is optional on construction, since we might know it only
	// after we get a viewport.
	SGE_CAMERA_SYMBOL
	parameters &
	projection(
		camera::projection_matrix const &);

	SGE_CAMERA_SYMBOL
	camera::optional_projection_matrix const &
	projection_matrix() const;
private:
	input::keyboard::device &keyboard_;
	spherical::movement_speed movement_speed_;
	spherical::is_active is_active_;
	spherical::coordinate_system::object coordinate_system_;
	spherical::action::mapping action_mapping_;
	spherical::origin origin_;
	spherical::minimum_radius minimum_radius_;
	spherical::maximum_radius maximum_radius_;
	spherical::acceleration_factor acceleration_factor_;
	spherical::damping_factor damping_factor_;
	camera::optional_projection_matrix projection_matrix_;
};
}
}
}

#endif

