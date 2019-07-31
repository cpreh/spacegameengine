//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_SPHERICAL_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_OBJECT_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/spherical/acceleration_factor.hpp>
#include <sge/camera/spherical/damping_factor.hpp>
#include <sge/camera/spherical/maximum_radius.hpp>
#include <sge/camera/spherical/minimum_radius.hpp>
#include <sge/camera/spherical/movement_speed.hpp>
#include <sge/camera/spherical/origin.hpp>
#include <sge/camera/spherical/parameters_fwd.hpp>
#include <sge/camera/spherical/action/mapping.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/input/keyboard/event/key_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace camera
{
namespace spherical
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
:
	public virtual sge::camera::base,
	public sge::camera::is_dynamic,
	public sge::camera::has_mutable_projection
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	explicit
	object(
		sge::camera::spherical::parameters const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::object
	coordinate_system() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::optional_projection_matrix
	projection_matrix() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update_projection_matrix(
		sge::camera::projection_matrix const &
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
	process_event(
		sge::input::event_base const &
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	~object()
	override;
private:
	sge::camera::spherical::action::mapping action_mapping_;

	sge::camera::spherical::movement_speed movement_speed_;

	sge::camera::spherical::origin origin_;

	sge::camera::spherical::minimum_radius minimum_radius_;

	sge::camera::spherical::maximum_radius maximum_radius_;

	sge::camera::spherical::acceleration_factor acceleration_factor_;

	sge::camera::spherical::damping_factor damping_factor_;

	sge::camera::spherical::coordinate_system::object coordinate_system_;

	sge::camera::optional_projection_matrix projection_matrix_;

	sge::camera::spherical::coordinate_system::object acceleration_;

	sge::camera::spherical::coordinate_system::object velocity_;

	bool increase_azimuth_pressed_, decrease_azimuth_pressed_;

	bool increase_inclination_pressed_, decrease_inclination_pressed_;

	bool increase_radius_pressed_, decrease_radius_pressed_;

	void
	key_event(
		sge::input::keyboard::event::key const &
	);
};

}
}
}

#endif

