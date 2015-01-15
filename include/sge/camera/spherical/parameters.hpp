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


#ifndef SGE_CAMERA_SPHERICAL_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_PARAMETERS_HPP_INCLUDED

#include <sge/camera/is_active.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/spherical/acceleration_factor.hpp>
#include <sge/camera/spherical/damping_factor.hpp>
#include <sge/camera/spherical/maximum_radius.hpp>
#include <sge/camera/spherical/minimum_radius.hpp>
#include <sge/camera/spherical/movement_speed.hpp>
#include <sge/camera/spherical/origin.hpp>
#include <sge/camera/spherical/action/mapping.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace camera
{
namespace spherical
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	parameters(
		sge::input::keyboard::device &,
		sge::camera::is_active,
		sge::camera::spherical::coordinate_system::object const &,
		sge::camera::spherical::action::mapping const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::input::keyboard::device &
	keyboard() const;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::is_active const
	is_active() const;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::coordinate_system::object const &
	coordinate_system() const;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::action::mapping const &
	action_mapping() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	movement_speed(
		sge::camera::spherical::movement_speed const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::movement_speed const &
	movement_speed() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	origin(
		sge::camera::spherical::origin const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::origin const &
	origin() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	minimum_radius(
		sge::camera::spherical::minimum_radius
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::minimum_radius const
	minimum_radius() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	maximum_radius(
		sge::camera::spherical::maximum_radius
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::maximum_radius const
	maximum_radius() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	acceleration_factor(
		sge::camera::spherical::acceleration_factor const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::acceleration_factor const &
	acceleration_factor() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	damping_factor(
		sge::camera::spherical::damping_factor const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::damping_factor const &
	damping_factor() const;

	// Projection is optional on construction, since we might know it only
	// after we get a viewport.
	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	projection(
		sge::camera::projection_matrix const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::optional_projection_matrix const &
	projection_matrix() const;
private:
	sge::input::keyboard::device &keyboard_;

	sge::camera::spherical::movement_speed movement_speed_;

	sge::camera::is_active const is_active_;

	sge::camera::spherical::coordinate_system::object const coordinate_system_;

	sge::camera::spherical::action::mapping const action_mapping_;

	sge::camera::spherical::origin origin_;

	sge::camera::spherical::minimum_radius minimum_radius_;

	sge::camera::spherical::maximum_radius maximum_radius_;

	sge::camera::spherical::acceleration_factor acceleration_factor_;

	sge::camera::spherical::damping_factor damping_factor_;

	sge::camera::optional_projection_matrix projection_matrix_;
};

}
}
}

#endif
