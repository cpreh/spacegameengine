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


#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/gizmo/to_rotation_matrix.hpp>
#include <sge/camera/projection/to_matrix.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/rotation_axis.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/numeric.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{
sge::renderer::scalar const epsilon =
	0.1f;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::camera::first_person::object::object(
	first_person::parameters const &params)
:
	camera::base(
		params.projection(),
		params.gizmo()),
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
	movement_speed_(
		params.movement_speed()),
	rotation_speed_(
		params.rotation_speed()),
	dirs_(
		renderer::vector3::null()),
	active_(
		params.active())
{
}
FCPPT_PP_POP_WARNING

sge::camera::first_person::object::~object()
{
}

void
sge::camera::first_person::object::active(
	bool _active)
{
	active_ =
		_active;
}

bool
sge::camera::first_person::object::active()
const
{
	return active_;
}

void
sge::camera::first_person::object::update(
	camera::duration const &d)
{
	base::gizmo().position(
		base::gizmo().position() +
		movement_speed_ *
		d.count() *
		boost::inner_product(
			base::gizmo().array(),
			dirs_,
			renderer::vector3::null()));
}

void
sge::camera::first_person::object::key_callback(
	input::keyboard::key_event const &k)
{
	if (!this->active())
		return;

	switch (k.key_code())
	{
		case input::keyboard::key_code::space:
			dirs_[1] = !k.pressed() ? 0.f : 1.f;
			break;
		case input::keyboard::key_code::lctrl:
			dirs_[1] = !k.pressed() ? 0.f : -1.f;
			break;
		case input::keyboard::key_code::w:
			dirs_[2] = !k.pressed() ? 0.f : 1.f;
			break;
		case input::keyboard::key_code::s:
			dirs_[2] = !k.pressed() ? 0.f : -1.f;
			break;
		case input::keyboard::key_code::a:
			dirs_[0] = !k.pressed() ? 0.f : -1.f;
			break;
		case input::keyboard::key_code::d:
			dirs_[0] = !k.pressed() ? 0.f : 1.f;
			break;
		default:
			break;
	}
}

void
sge::camera::first_person::object::mouse_axis_callback(
	input::mouse::axis_event const &k)
{
	if (!this->active())
		return;

	renderer::scalar const angle =
		static_cast<renderer::scalar>(k.value())/rotation_speed_;

	switch (k.code())
	{
		// What's the use...
		case input::mouse::axis_code::unknown:
			break;
		case input::mouse::axis_code::x:
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
						base::gizmo().forward(),
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

		base::gizmo()
			.position(base::gizmo().position())
			.forward(normalize(forward))
			.up(normalize(up))
			.right(normalize(right));
		}
		break;
		case input::mouse::axis_code::y:
		{
			using fcppt::math::matrix::rotation_axis;
			using fcppt::math::vector::narrow_cast;
			using fcppt::math::vector::construct;

			if(
				(fcppt::math::vector::length(
					renderer::vector3(
						0.f,
						-1.f,
						0.f) -
					base::gizmo().forward()) < epsilon &&
					angle > 0.f) ||
				(fcppt::math::vector::length(
					renderer::vector3(
						0.f,
						1.f,
						0.f) -
					base::gizmo().forward()) < epsilon &&
					angle < 0.f))
				return;

			renderer::vector3
				forward =
					narrow_cast<renderer::vector3>(
						rotation_axis(
							angle,
							base::gizmo().right()) *
						construct(
							base::gizmo().forward(),
							static_cast<renderer::scalar>(0))),
				up =
					cross(forward,base::gizmo().right()),
				right =
					cross(up,forward);

			base::gizmo()
				.position(base::gizmo().position())
				.forward(normalize(forward))
				.up(normalize(up))
				.right(normalize(right));
		}
		break;
		case input::mouse::axis_code::wheel:
		break;
	}
}
