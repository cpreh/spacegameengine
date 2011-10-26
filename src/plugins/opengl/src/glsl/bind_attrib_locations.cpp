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


#include <sge/opengl/glsl/bind_attrib_locations.hpp>
#include <sge/opengl/glsl/programfuncs/bind_attrib_location.hpp>
#include <sge/opengl/glsl/instantiate.hpp>
#include <sge/opengl/vertex_declaration.hpp>
#include <sge/opengl/vf/attribute_location_container.hpp>

template<
	typename Environment
>
void
sge::opengl::glsl::bind_attrib_locations(
	typename Environment::program_context const &_context,
	typename Environment::handle const _handle,
	renderer::vertex_declaration const &_declaration
)
{
	vf::attribute_location_container const &locations(
		dynamic_cast<
			opengl::vertex_declaration const &
		>(
			_declaration
		).attribute_locations()
	);

	for(
		vf::attribute_location_container::const_iterator it(
			locations.begin()
		);
		it != locations.end();
		++it
	)
		glsl::programfuncs::bind_attrib_location<
			Environment
		>(
			_context,
			_handle,
			it->location(),
			it->name().c_str()
		);
}

#define SGE_OPENGL_GLSL_INSTANTIATE_BIND_ATTRIB_LOCATIONS(\
	env\
)\
template \
void \
sge::opengl::glsl::bind_attrib_locations<\
	env\
>(\
	env::program_context const &,\
	env::handle,\
	sge::renderer::vertex_declaration const &\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_BIND_ATTRIB_LOCATIONS
)
