/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/constant_attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/linear_attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/quadratic_attenuation.hpp>


sge::renderer::state::ffp::lighting::light::attenuation::attenuation(
	sge::renderer::state::ffp::lighting::light::constant_attenuation const _constant,
	sge::renderer::state::ffp::lighting::light::linear_attenuation const _linear,
	sge::renderer::state::ffp::lighting::light::quadratic_attenuation const _quadratic
)
:
	constant_(
		_constant
	),
	linear_(
		_linear
	),
	quadratic_(
		_quadratic
	)
{
}

sge::renderer::state::ffp::lighting::light::constant_attenuation const
sge::renderer::state::ffp::lighting::light::attenuation::constant() const
{
	return constant_;
}

sge::renderer::state::ffp::lighting::light::linear_attenuation const
sge::renderer::state::ffp::lighting::light::attenuation::linear() const
{
	return linear_;
}

sge::renderer::state::ffp::lighting::light::quadratic_attenuation const
sge::renderer::state::ffp::lighting::light::attenuation::quadratic() const
{
	return quadratic_;
}
