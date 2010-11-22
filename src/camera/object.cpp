#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/gizmo/to_rotation_matrix.hpp>
#include <sge/camera/projection/to_matrix.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/mouse/device.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/matrix/rotation_axis.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/algorithm/inner_product.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/variant/object.hpp>
// FFFFFFFFFFFFFFFFFFFFFFFUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU
#include <fcppt/function/object.hpp>
#include <boost/bind.hpp>
#include <algorithm>

sge::camera::object::object(
	parameters const &params)
:
	keyboard_connection_(
		params.keyboard().key_callback(
			boost::bind(
				&object::key_callback,
				this,
				_1))),
	mouse_axis_connection_(
		params.mouse().axis_callback(
			boost::bind(
				&object::mouse_axis_callback,
				this,
				_1))),
	projection_(
		params.projection()),
	projection_matrix_(
		projection::to_matrix(
			projection_)),
	movement_speed_(
		params.movement_speed()),
	rotation_speed_(
		params.rotation_speed()),
	gizmo_(
		gizmo_type()
			.position(
				params.position())
			.forward(
				renderer::vector3(0,0,1))
			.up(
				renderer::vector3(0,1,0))
			.right(
				renderer::vector3(1,0,0))),
	dirs_(
		renderer::vector3::null())
{
}

sge::camera::object::~object()
{
}

void
sge::camera::object::update(
	renderer::scalar const time_delta)
{
//	fcppt::io::cout << "Gizmo is: " << gizmo_.forward() << ", " << gizmo_.up() << ", " << gizmo_.right() << ", position: " << gizmo_.position() << "\n";
	gizmo_.position( 
		gizmo_.position() + 
		movement_speed_ * 
		time_delta * 
		fcppt::algorithm::inner_product(
			gizmo_.array(),
			dirs_,
			renderer::vector3::null()));
}

sge::renderer::matrix4 const
sge::camera::object::world() const
{
	return 
		rotation() * 
		translation();
}

sge::renderer::matrix4 const
sge::camera::object::rotation() const
{
	return 
		gizmo::to_rotation_matrix(
			gizmo_);
}

sge::renderer::matrix4 const
sge::camera::object::translation() const
{
	return 
		fcppt::math::matrix::translation(
			-gizmo_.position());
}

sge::renderer::matrix4 const
sge::camera::object::projection() const
{
	return projection_matrix_;
}

sge::renderer::matrix4 const 
sge::camera::object::mvp() const
{
	return
		projection() * world();
}

sge::camera::gizmo_type const &
sge::camera::object::gizmo() const
{
	return gizmo_;
}

sge::camera::gizmo_type &
sge::camera::object::gizmo()
{
	return gizmo_;
}

void
sge::camera::object::key_callback(
	sge::input::keyboard::key_event const &k)
{
	switch (k.key().code())
	{
		case sge::input::keyboard::key_code::space:
			dirs_[1] = !k.pressed() ? 0 : 1;
			break;
		case sge::input::keyboard::key_code::lctrl:
			dirs_[1] = !k.pressed() ? 0 : -1;
			break;
		case sge::input::keyboard::key_code::up:
			dirs_[2] = !k.pressed() ? 0 : -1;
			break;
		case sge::input::keyboard::key_code::down:
			dirs_[2] = !k.pressed() ? 0 : 1;
			break;
		case sge::input::keyboard::key_code::left:
			dirs_[0] = !k.pressed() ? 0 : -1;
			break;
		case sge::input::keyboard::key_code::right:
			dirs_[0] = !k.pressed() ? 0 : 1;
			break;
		default:
			break;
	}
}

void
sge::camera::object::mouse_axis_callback(
	sge::input::mouse::axis_event const &k)
{
	renderer::scalar const angle = 
		static_cast<renderer::scalar>(k.axis_value())/rotation_speed_;

	switch (k.axis())
	{
		case sge::input::mouse::axis::x:
		{
		using fcppt::math::matrix::rotation_axis;
		using fcppt::math::vector::narrow_cast;
		using fcppt::math::vector::construct;
		using fcppt::math::vector::normalize;

		renderer::vector3 
			forward = 
				narrow_cast<renderer::vector3>(
					rotation_axis(
						-angle,
						renderer::vector3(0,1,0)) *
					construct(
						gizmo_.forward(),
						// Cast neccesary here
						static_cast<renderer::scalar>(0))),
			right = 
				cross(
					renderer::vector3(0,1,0),
					forward),
			up = 
				cross(
					forward,
					right); 

		gizmo_ 
			.position(gizmo_.position())
			.forward(normalize(forward))
			.up(normalize(up))
			.right(normalize(right));
		}
		break;
		case sge::input::mouse::axis::y:
		{
			using fcppt::math::matrix::rotation_axis;
			using fcppt::math::vector::narrow_cast;
			using fcppt::math::vector::construct;

			renderer::vector3 
				forward = 
					narrow_cast<renderer::vector3>(
						rotation_axis(
							-angle,
							gizmo_.right()) *
						construct(
							gizmo_.forward(),
							static_cast<renderer::scalar>(0))),
				up = 
					cross(forward,gizmo_.right()),
				right = 
					cross(up,forward); 

			gizmo_
				.position(gizmo_.position())
				.forward(normalize(forward))
				.up(normalize(up))
				.right(normalize(right));
		}
		break;
		case sge::input::mouse::axis::wheel:
		break;
	}
}
