//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_FIRST_PERSON_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_OBJECT_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/has_mutable_coordinate_system.hpp>
#include <sge/camera/has_mutable_projection.hpp>
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
#include <sge/input/event_base_fwd.hpp>
#include <sge/input/keyboard/event/key_fwd.hpp>
#include <sge/input/mouse/event/axis_fwd.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace camera
{
namespace first_person
{

// NOLINTNEXTLINE(fuchsia-multiple-inheritance)
class SGE_CORE_DETAIL_CLASS_SYMBOL object
:
	public virtual sge::camera::base,
	public sge::camera::is_dynamic,
	public sge::camera::has_mutable_projection,
	public sge::camera::has_mutable_coordinate_system
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	explicit
	object(
		sge::camera::first_person::parameters const &
	);

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::object
	coordinate_system() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update_coordinate_system(
		sge::camera::coordinate_system::object const &
	)
	override;

	[[nodiscard]]
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
	process_event(
		sge::input::event_base const &
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
	sge::camera::first_person::action::mapping action_mapping_;

	sge::camera::first_person::movement_speed movement_speed_;

	sge::camera::first_person::mouse_speed_multiplier mouse_speed_multiplier_;

	sge::renderer::vector3 directions_;

	sge::camera::coordinate_system::object coordinate_system_;

	sge::camera::optional_projection_matrix projection_matrix_;

	bool left_pressed_, right_pressed_;

	bool up_pressed_, down_pressed_;

	bool forward_pressed_, backward_pressed_;

	void
	key_event(
		sge::input::keyboard::event::key const &
	);

	void
	mouse_axis_event(
		sge::input::mouse::event::axis const &
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
