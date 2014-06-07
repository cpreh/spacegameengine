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


#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_color.hpp>
#include <sge/renderer/state/ffp/lighting/specular_color.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/light/variant.hpp>


sge::renderer::state::ffp::lighting::light::parameters::parameters(
	sge::renderer::state::ffp::lighting::diffuse_color const &_diffuse,
	sge::renderer::state::ffp::lighting::specular_color const &_specular,
	sge::renderer::state::ffp::lighting::ambient_color const &_ambient,
	sge::renderer::state::ffp::lighting::light::variant const &_variant
)
:
	diffuse_(
		_diffuse
	),
	specular_(
		_specular
	),
	ambient_(
		_ambient
	),
	variant_(
		_variant
	)
{
}

sge::renderer::state::ffp::lighting::diffuse_color const &
sge::renderer::state::ffp::lighting::light::parameters::diffuse() const
{
	return diffuse_;
}

sge::renderer::state::ffp::lighting::specular_color const &
sge::renderer::state::ffp::lighting::light::parameters::specular() const
{
	return specular_;
}

sge::renderer::state::ffp::lighting::ambient_color const &
sge::renderer::state::ffp::lighting::light::parameters::ambient() const
{
	return ambient_;
}

sge::renderer::state::ffp::lighting::light::variant const &
sge::renderer::state::ffp::lighting::light::parameters::variant() const
{
	return variant_;
}
