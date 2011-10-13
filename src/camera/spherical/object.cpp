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

#include <fcppt/math/vector/output.hpp>

#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/cross.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/matrix/rotation_x.hpp>
#include <fcppt/math/matrix/rotation_y.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/math/vector/hypersphere_to_cartesian.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <sge/camera/duration.hpp>
#include <sge/camera/spherical/object.hpp>
#include <sge/camera/spherical/parameters.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

namespace
{
sge::renderer::scalar const epsilon =
	0.01f;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::camera::spherical::object::object(
	spherical::parameters const &params)
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
	movement_speed_(
		params.movement_speed()),
	min_radius_(
		params.min_radius()),
	dirs_(
		sge::renderer::vector3::null()),
	radius_(
		params.radius()),
	angles_(
		fcppt::math::pi<sge::renderer::scalar>() *
			static_cast<sge::renderer::scalar>(0.5f),
		0.f),
	active_(
		params.active())
{
}
FCPPT_PP_POP_WARNING

sge::camera::spherical::object::~object()
{
}

void
sge::camera::spherical::object::update(
	sge::camera::duration const &d)
{
	sge::renderer::scalar pi = fcppt::math::pi<sge::renderer::scalar>();
	radius_ = std::max(
		radius_ + dirs_[0] * movement_speed_ * d.count(),
		min_radius_);

	angles_ = renderer::vector2(
			fcppt::math::clamp(
				angles_[0] + dirs_[1] * movement_speed_ * d.count(),
					epsilon,
				  pi - epsilon),
				angles_[1] + dirs_[2] * movement_speed_ * d.count()
	);

	using fcppt::math::matrix::rotation_y;
	using fcppt::math::matrix::rotation_x;
	using fcppt::math::vector::narrow_cast;
	using fcppt::math::vector::normalize;
	using fcppt::math::vector::cross;

	sge::renderer::vector3 pos =
		sge::renderer::vector3(
			radius_ * std::sin(angles_[0]) * std::cos(angles_[1]),
			radius_ * std::cos(angles_[0]),
			radius_ * std::sin(angles_[0]) * std::sin(angles_[1]));

	sge::renderer::vector3 t0 = -pos;
	sge::renderer::vector3 t1 = cross(
		t0,
		sge::renderer::vector3(0.f,1.f,0.f));
	sge::renderer::vector3 t2 = cross(t1,t0);

	base::gizmo()
		.position(pos)
		.forward(normalize(t0))
		.right(normalize(t1))
		.up(normalize(t2));
}

void
sge::camera::spherical::object::active(
	bool const _active)
{
	active_ =
		_active;
}

bool
sge::camera::spherical::object::active() const
{
	return active_;
}

void
sge::camera::spherical::object::key_callback(
	input::keyboard::key_event const &k)
{
	if (!this->active())
		return;

	switch (k.key_code())
	{
		// radius
		case input::keyboard::key_code::space:
			dirs_[0] = !k.pressed() ? 0.f : 1.f;
			break;
		case input::keyboard::key_code::lctrl:
			dirs_[0] = !k.pressed() ? 0.f : -1.f;
			break;
		// theta
		case input::keyboard::key_code::w:
			dirs_[1] = !k.pressed() ? 0.f : -1.f;
			break;
		case input::keyboard::key_code::s:
			dirs_[1] = !k.pressed() ? 0.f : 1.f;
			break;
		// phi
		case input::keyboard::key_code::a:
			dirs_[2] = !k.pressed() ? 0.f : 1.f;
			break;
		case input::keyboard::key_code::d:
			dirs_[2] = !k.pressed() ? 0.f : -1.f;
			break;
		default:
			break;
	}
}
