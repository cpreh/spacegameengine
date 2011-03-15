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


#include "../create_shader.hpp"
#include "../shader.hpp"
#include "../context.hpp"
#include "../vertex_shader.hpp"
#include "../pixel_shader.hpp"
#include "../native/environment.hpp"
#include "../arb/environment.hpp"
#include "../../context/use.hpp"
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/shared_ptr.hpp>

template<
	typename Shader
>
fcppt::shared_ptr<
	typename Shader::base_type
> const
sge::opengl::glsl::create_shader(
	opengl::context::object &_context,
	sge::renderer::glsl::string const &_source
)
{
	typedef fcppt::shared_ptr<
		typename Shader::base_type
	> ret_type;

	return
		opengl::context::use<
			glsl::context
		>(
			_context
		).is_native()
		?
			ret_type(
				fcppt::make_shared_ptr<
					glsl::shader<
						Shader,
						native::environment
					>
				>(
					fcppt::ref(
						_context
					),
					_source
				)
			)
		:
			ret_type(
				fcppt::make_shared_ptr<
					glsl::shader<
						Shader,
						arb::environment
					>
				>(
					fcppt::ref(
						_context
					),
					_source
				)
			)
		;
}

#define SGE_OPENGL_GLSL_CREATE_SHADER(type) \
template \
fcppt::shared_ptr<\
	type::base_type\
> const \
sge::opengl::glsl::create_shader<\
	type\
>(\
	sge::opengl::context::object &, \
	sge::renderer::glsl::string const &\
);

SGE_OPENGL_GLSL_CREATE_SHADER(
	sge::opengl::glsl::vertex_shader
)

SGE_OPENGL_GLSL_CREATE_SHADER(
	sge::opengl::glsl::pixel_shader
)

#undef SGE_OPENGL_GLSL_CREATE_SHADER
