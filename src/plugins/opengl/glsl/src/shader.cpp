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


#include "../shader.hpp"
#include "../shaderfuncs/compile.hpp"
#include "../shaderfuncs/get_integer.hpp"
#include "../shaderfuncs/compile_status.hpp"
#include "../shaderfuncs/info_log.hpp"
#include "../shaderfuncs/info_log_length.hpp"
#include "../format_error.hpp"
#include "../get_shader_source.hpp"
#include "../geometry_shader.hpp"
#include "../instantiate.hpp"
#include "../make_shader_type.hpp"
#include "../pixel_shader.hpp"
#include "../set_shader_source.hpp"
#include "../shader_contexts.hpp"
#include "../vertex_shader.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <fcppt/text.hpp>


template<
	typename Type,
	typename Environment
>
sge::opengl::glsl::shader<Type, Environment>::shader(
	opengl::context::object &_context,
	sge::renderer::glsl::string const &_source
)
:
	base_type(),
	glsl_base(
		_context,
		glsl::make_shader_type<
			Environment
		>(
			opengl::context::use<
				typename Environment::shader_context
			>(
				_context
			),
			Type::shader_type()
		)
	)
{
	glsl::set_shader_source<
		Environment
	>(
		this->context(),
		this->id(),
		_source
	);
}

template<
	typename Type,
	typename Environment
>
sge::opengl::glsl::shader<Type, Environment>::~shader()
{
}

template<
	typename Type,
	typename Environment
>
void
sge::opengl::glsl::shader<Type, Environment>::compile()
{
	shaderfuncs::compile<
		Environment
	>(
		this->context(),
		this->id()
	);

	if(
		shaderfuncs::compile_status<
			Environment
		>(
			this->context(),
			this->id()
		)
		== GL_FALSE
	)
		throw sge::renderer::glsl::exception(
			FCPPT_TEXT("Compiling a ")
			+ Type::shader_name()
			+ FCPPT_TEXT(" shader failed:\n")
			+ this->info_log()
		);
}

template<
	typename Type,
	typename Environment
>
fcppt::string const
sge::opengl::glsl::shader<Type, Environment>::info_log() const
{
	return
		glsl::format_error(
			&shaderfuncs::info_log<
				Environment
			>,
			&shaderfuncs::info_log_length<
				Environment
			>,
			this->id(),
			this->context()
		);
}

template<
	typename Type,
	typename Environment
>
sge::renderer::glsl::string const
sge::opengl::glsl::shader<Type, Environment>::source() const
{
	return
		glsl::get_shader_source<
			Environment
		>(
			this->context(),
			this->id()
		);
}

#define SGE_OPENGL_GLSL_INSTANTIATE_SHADER_CONCRETE(\
	shader_type,\
	env\
)\
template class sge::opengl::glsl::shader<\
	shader_type,\
	env\
>;

#define SGE_OPENGL_GLSL_INSTANTIATE_SHADER(\
	env\
)\
SGE_OPENGL_GLSL_INSTANTIATE_SHADER_CONCRETE(\
	sge::opengl::glsl::vertex_shader,\
	env\
)\
SGE_OPENGL_GLSL_INSTANTIATE_SHADER_CONCRETE(\
	sge::opengl::glsl::pixel_shader,\
	env\
)\
SGE_OPENGL_GLSL_INSTANTIATE_SHADER_CONCRETE(\
	sge::opengl::glsl::geometry_shader,\
	env\
)

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_SHADER
)
