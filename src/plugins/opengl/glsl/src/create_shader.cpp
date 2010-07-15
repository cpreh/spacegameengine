/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../create_shader.hpp"
#include "../context.hpp"
#include "../vertex_shader.hpp"
#include "../pixel_shader.hpp"
#include "../normal/environment.hpp"
#include "../arb/environment.hpp"
#include "../../context/use.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>

template<
	typename Shader
>
fcppt::shared_ptr<Shader> const
sge::opengl::glsl::create_shader(
	opengl::context::object &_context,
	sge::renderer::glsl::string const &_source
)
{
	return
		opengl::context::use<
			glsl::context
		>(
			_context
		).is_native()
		?
			fcppt::make_shared_ptr<
				Shader<
					normal::environment
				>()
			>(
				std::tr1::ref(
					_vertex
				)
			)
		:
			fcppt::make_shared_ptr<
				Shader<
					normal::environment
				>()
			>(
				std::tr1::ref(
					_vertex
				)
			)
		;
}

#define SGE_OPENGL_GLSL_CREATE_SHADER(shader) \
template \
fcppt::shared_ptr<shader> \
sge::opengl::glsl::create_shader(\
	opengl::context::object &, \
	sge::renderer::glsl::string const &\
);

SGE_OPENGL_GLSL_CREATE_SHADER(
	sge::opengl::glsl::vertex_shader
)

SGE_OPENGL_GLSL_CREATE_SHADER(
	sge::opengl::glsl::pixel_shader
)

#undef SGE_OPENGL_GLSL_CREATE_SHADER
