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


#include "../shader.hpp"
#include "../shader_functions.hpp"
#include "../format_error.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>

template<
	typename Environment
>
sge::opengl::glsl::shader<Environment>::shader(
	GLenum const _type,
	renderer::glsl::string const &_source
)
:
	id_(
		shaderfuncs::create<
			Environment
		>(
			_context,
			_type
		)
	)
{
	const char* const ptr = source.c_str();

	const GLint len = static_cast<GLint>(source.size());

	shader_source<Native>(
		id(),
		1,
		const_cast<const char**>(&ptr),
		&len
	);

	compile_shader<Native>(id());

	if(
		compile_status<Native>(id()) == GL_FALSE
	)
		throw sge::renderer::glsl::exception(
			FCPPT_TEXT("Compiling a shader failed:\n")
			+ info_log()
		);
}

template<
	bool Native
>
sge::opengl::glsl::shader<Native>::~shader()
{
	delete_shader<Native>(id());
}

template<
	bool Native
>
typename sge::opengl::glsl::traits<Native>::handle
sge::opengl::glsl::shader<Native>::id() const
{
	return id_;
}

template<
	bool Native
>
fcppt::string const
sge::opengl::glsl::shader<Native>::info_log() const
{
	return
		format_error(
			&shader_info_log<
				Native
			>,
			&shader_info_log_length<
				Native
			>,
			id()
		);
}

template class sge::opengl::glsl::shader<true>;
template class sge::opengl::glsl::shader<false>;
