//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_SPHERICAL_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_PARAMETERS_HPP_INCLUDED

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


namespace sge
{
namespace camera
{
namespace spherical
{

class parameters
{
public:
	SGE_CAMERA_DETAIL_SYMBOL
	parameters(
		sge::camera::spherical::coordinate_system::object const &,
		sge::camera::spherical::action::mapping const &
	);

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::coordinate_system::object const &
	coordinate_system() const;

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::action::mapping const &
	action_mapping() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	movement_speed(
		sge::camera::spherical::movement_speed const &
	);

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::movement_speed const &
	movement_speed() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	origin(
		sge::camera::spherical::origin const &
	);

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::origin const &
	origin() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	minimum_radius(
		sge::camera::spherical::minimum_radius
	);

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::minimum_radius
	minimum_radius() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	maximum_radius(
		sge::camera::spherical::maximum_radius
	);

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::maximum_radius
	maximum_radius() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	acceleration_factor(
		sge::camera::spherical::acceleration_factor const &
	);

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::spherical::acceleration_factor const &
	acceleration_factor() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	damping_factor(
		sge::camera::spherical::damping_factor const &
	);

	[[nodiscard]]
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

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::optional_projection_matrix const &
	projection_matrix() const;
private:
	sge::camera::spherical::movement_speed movement_speed_;

	sge::camera::spherical::coordinate_system::object coordinate_system_;

	sge::camera::spherical::action::mapping action_mapping_;

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
