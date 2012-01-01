/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/d3d9/convert/light/object.hpp>
#include <sge/d3d9/convert/light/visitor.hpp>
#include <sge/renderer/light/object.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


D3DLIGHT9 const
sge::d3d9::convert::light::object(
	sge::renderer::light::object const &_light
)
{
	D3DLIGHT9 ret;

	fcppt::variant::apply_unary(
			convert::light::visitor(
				ret
			),
			_light.variant()
		);

	ret.Diffuse
		= d3d9::convert::to_color_value(
			_light.diffuse().get()
		);

	ret.Specular
		= d3d9::convert::to_color_value(
			_light.specular().get()
		);

	ret.Ambient
		= d3d9::convert::to_color_value(
			_light.ambient().get()
		);

	ret.Range =
		std::sqrt(
			FLT_MAX
		);

	ret.Falloff = 1.0f;

	return ret;
}
