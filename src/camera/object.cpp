/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/gizmo/to_rotation_matrix.hpp>
#include <sge/camera/projection/to_matrix.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/matrix/rotation_axis.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/chrono/duration_impl.hpp>
// FFFFFFFFFFFFFFFFFFFFFFFUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <boost/range/numeric.hpp>

sge::camera::object::object(
	camera::parameters const &params)
:
	keyboard_connection_(
		params.keyboard().key_callback(
			std::tr1::bind(
				&object::key_callback,
				this,
				std::tr1::placeholders::_1))),
	mouse_axis_connection_(
		params.mouse().axis_callback(
			std::tr1::bind(
				&object::mouse_axis_callback,
				this,
				std::tr1::placeholders::_1))),
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
		params.gizmo()),
	dirs_(
		renderer::vector3::null()),
	active_(
		params.active())
{
}

sge::camera::object::~object()
{
}

void
sge::camera::object::update(
	camera::duration const &d)
{
	//std::cout << "count: " << d.count() << "\n";
	gizmo_.position( 
		gizmo_.position() + 
		movement_speed_ * 
		d.count() * 
		boost::inner_product(
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

sge::camera::projection::object const
sge::camera::object::projection_object() const
{
	return projection_;
}

void
sge::camera::object::projection_object(
	projection::object const &_projection)
{
	projection_ = 
		_projection;
	projection_matrix_ = 
		projection::to_matrix(
			projection_);
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
sge::camera::object::active(
	bool const _active)
{
	active_ = 
		_active;
}

bool
sge::camera::object::active() const
{
	return active_;
}

void
sge::camera::object::key_callback(
	sge::input::keyboard::key_event const &k)
{
	if (!active())
		return;

	switch (k.key_code())
	{
		case sge::input::keyboard::key_code::space:
			dirs_[1] = !k.pressed() ? 0.f : 1.f;
			break;
		case sge::input::keyboard::key_code::lctrl:
			dirs_[1] = !k.pressed() ? 0.f : -1.f;
			break;
		case sge::input::keyboard::key_code::w:
			dirs_[2] = !k.pressed() ? 0.f : 1.f;
			break;
		case sge::input::keyboard::key_code::s:
			dirs_[2] = !k.pressed() ? 0.f : -1.f;
			break;
		case sge::input::keyboard::key_code::a:
			dirs_[0] = !k.pressed() ? 0.f : -1.f;
			break;
		case sge::input::keyboard::key_code::d:
			dirs_[0] = !k.pressed() ? 0.f : 1.f;
			break;
		default:
			break;
	}
}

void
sge::camera::object::mouse_axis_callback(
	sge::input::mouse::axis_event const &k)
{
	if (!active())
		return;

	renderer::scalar const angle = 
		static_cast<renderer::scalar>(k.axis_value())/rotation_speed_;

	switch (k.axis())
	{
		// What's the use...
		case sge::input::mouse::axis::unknown:
			break;
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
						angle,
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
							angle,
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
