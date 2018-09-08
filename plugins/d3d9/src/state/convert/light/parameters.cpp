/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_color_value.hpp>
#include <sge/d3d9/state/convert/light/parameters.hpp>
#include <sge/d3d9/state/convert/light/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cfloat>
#include <cmath>
#include <fcppt/config/external_end.hpp>


D3DLIGHT9 const
sge::d3d9::state::convert::light::parameters(
	sge::renderer::state::ffp::lighting::light::parameters const &_light
)
{
	D3DLIGHT9 ret;

	fcppt::variant::apply(
			sge::d3d9::state::convert::light::visitor(
				ret
			),
			_light.variant()
		);

	ret.Diffuse
		= sge::d3d9::convert::to_color_value(
			_light.diffuse().get()
		);

	ret.Specular
		= sge::d3d9::convert::to_color_value(
			_light.specular().get()
		);

	ret.Ambient
		= sge::d3d9::convert::to_color_value(
			_light.ambient().get()
		);

	ret.Range =
		std::sqrt(
			FLT_MAX
		);

	ret.Falloff = 1.0f;

	return ret;
}
