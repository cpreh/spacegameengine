#ifndef SGE_CAMERA_FIRST_PERSON_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_PARAMETERS_HPP_INCLUDED

#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/first_person/is_active.hpp>
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
public:
	SGE_CAMERA_SYMBOL
	explicit
	parameters(
		sge::input::keyboard::device &,
		sge::input::mouse::device &,
		first_person::is_active const &,
		first_person::movement_speed const &,
		camera::coordinate_system::object const &);

	SGE_CAMERA_SYMBOL
	sge::input::keyboard::device &
	keyboard() const;

	SGE_CAMERA_SYMBOL
	sge::input::mouse::device &
	mouse() const;

	SGE_CAMERA_SYMBOL
	first_person::is_active const &
	is_active() const;

	SGE_CAMERA_SYMBOL
	parameters &
	action_mapping(
		action::mapping const &);

	SGE_CAMERA_SYMBOL
	action::mapping const &
	action_mapping() const;

	SGE_CAMERA_SYMBOL
	camera::first_person::movement_speed const &
	movement_speed() const;

	SGE_CAMERA_SYMBOL
	camera::coordinate_system::object const &
	coordinate_system() const;

	SGE_CAMERA_SYMBOL
	parameters &
	mouse_speed_multiplier(
		camera::first_person::mouse_speed_multiplier const &);

	SGE_CAMERA_SYMBOL
	camera::first_person::mouse_speed_multiplier const &
	mouse_speed_multiplier() const;

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
	sge::input::keyboard::device &keyboard_;
	sge::input::mouse::device &mouse_;
	first_person::is_active is_active_;
	action::mapping action_mapping_;
	camera::first_person::movement_speed movement_speed_;
	camera::coordinate_system::object coordinate_system_;
	camera::first_person::mouse_speed_multiplier mouse_speed_multiplier_;
	camera::optional_projection_matrix projection_matrix_;
};
}
}
}

#endif

