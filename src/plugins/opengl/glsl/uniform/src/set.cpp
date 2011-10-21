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
#include "../set_visitor.hpp"
#include "../type.hpp"
#include "../../instantiate.hpp"
#include <sge/renderer/glsl/uniform/value.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


template<
	typename Environment
>
sge::opengl::glsl::uniform::type const
sge::opengl::glsl::uniform::set(
	typename Environment::uniform_context const &_context,
	GLint const _location,
	renderer::glsl::uniform::value const &_value
)
{
	return
		fcppt::variant::apply_unary(
			uniform::set_visitor<
				Environment
			>(
				_context,
				_location
			),
			_value
		);
}

#define SGE_OPENGL_GLSL_INSTANTIATE_UNIFORM_SET(\
	env\
)\
template \
sge::opengl::glsl::uniform::type const \
sge::opengl::glsl::uniform::set<\
	env\
>(\
	env::uniform_context const &,\
	GLint,\
	sge::renderer::glsl::uniform::value const &\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_UNIFORM_SET
)
