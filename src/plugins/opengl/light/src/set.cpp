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


#include "../set.hpp"
#include "../color.hpp"
#include "../index.hpp"
#include "../visitor.hpp"
#include "../../convert/light_index.hpp"
#include <sge/renderer/light/object.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>

void
sge::opengl::light::set(
	renderer::light::index const _index,
	renderer::light::object const &_light
)
{
	light::index const glindex(
		convert::light_index(
			_index
		)
	);

	light::color(
		glindex,
		GL_AMBIENT,
		_light.ambient().get()
	);

	light::color(
		glindex,
		GL_DIFFUSE,
		_light.diffuse().get()
	);

	light::color(
		glindex,
		GL_SPECULAR,
		_light.specular().get()
	);

	fcppt::variant::apply_unary(
		light::visitor(
			glindex
		),
		_light.variant()
	);
}
