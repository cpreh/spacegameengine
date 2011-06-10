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


#include "../program.hpp"
#include "../attachment.hpp"
#include "../bind_attrib_locations.hpp"
#include "../format_error.hpp"
#include "../instantiate.hpp"
#include "../program_contexts.hpp"
#include "../uniform/variable.hpp"
#include "../programfuncs/bind_frag_data_location.hpp"
#include "../programfuncs/info_log.hpp"
#include "../programfuncs/info_log_length.hpp"
#include "../programfuncs/link.hpp"
#include "../programfuncs/link_status.hpp"
#include "../programfuncs/use.hpp"
#include "../uniform/contexts.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <sge/renderer/glsl/geometry_shader.hpp>
#include <sge/renderer/glsl/pixel_shader.hpp>
#include <sge/renderer/glsl/shader.hpp>
#include <sge/renderer/glsl/vertex_shader.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

template<
	typename Environment
>
sge::opengl::glsl::program<Environment>::program(
	opengl::context::object &_context
)
:
	renderer::glsl::program(),
	program_base(),
	holder_(
		_context
	),
	uniform_context_(
		opengl::context::use<
			typename Environment::uniform_context
		>(
			_context
		)
	),
	vertex_shader_(),
	pixel_shader_(),
	geometry_shader_()
{}

template<
	typename Environment
>
sge::opengl::glsl::program<Environment>::~program()
{
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::use() const
{
	do_use(
		holder_.id()
	);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::unuse() const
{
	do_use(
		0
	);
}

template<
	typename Environment
>
sge::renderer::glsl::uniform::variable_ptr const
sge::opengl::glsl::program<Environment>::uniform(
	renderer::glsl::string const &_name
)
{
	return
		fcppt::make_shared_ptr<
			uniform::variable<
				Environment
			>
		>(
			fcppt::cref(
				uniform_context_
			),
			holder_.id(),
			_name
		);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::vertex_declaration(
	renderer::vertex_declaration const &_declaration
)
{
	glsl::bind_attrib_locations<
		Environment
	>(
		holder_.context(),
		holder_.id(),
		_declaration
	);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::vertex_shader(
	sge::renderer::glsl::vertex_shader_ptr const _pointer
)
{
	vertex_shader_.take(
		make_attachment(
			_pointer
		)
	);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::pixel_shader(
	sge::renderer::glsl::pixel_shader_ptr const _pointer
)
{
	pixel_shader_.take(
		make_attachment(
			_pointer
		)
	);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::geometry_shader(
	sge::renderer::glsl::geometry_shader_ptr const _pointer
)
{
	geometry_shader_.take(
		make_attachment(
			_pointer
		)
	);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::color_surface_location(
	renderer::stage_type const _stage,
	renderer::glsl::string const &_name
)
{
	programfuncs::bind_frag_data_location<
		Environment
	>(
		holder_.context(),
		holder_.id(),
		static_cast<
			GLuint
		>(
			_stage.get()
		),
		_name.c_str()
	);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::link()
{
	programfuncs::link<
		Environment
	>(
		holder_.context(),
		holder_.id()
	);

	if(
		programfuncs::link_status<
			Environment
		>(
			holder_.context(),
			holder_.id()
		)
		== GL_FALSE
	)
		throw sge::renderer::glsl::exception(
			FCPPT_TEXT("Compiling a program failed:\n")
			+ info_log()
		);
}

template<
	typename Environment
>
fcppt::string const
sge::opengl::glsl::program<Environment>::info_log() const
{
	return
		glsl::format_error(
			&programfuncs::info_log<
				Environment
			>,
			&programfuncs::info_log_length<
				Environment
			>,
			holder_.id(),
			holder_.context()
		);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::do_use(
	handle const _handle
) const
{
	programfuncs::use<
		Environment
	>(
		holder_.context(),
		_handle
	);
}

template<
	typename Environment
>
typename sge::opengl::glsl::program<Environment>::attachment_unique_ptr
sge::opengl::glsl::program<Environment>::make_attachment(
	sge::renderer::glsl::shader_ptr const _shader
)
{
	return
		fcppt::make_unique_ptr<
			attachment_type
		>(
			fcppt::cref(
				holder_.context()
			),
			_shader,
			holder_.id()
		);
}

#define SGE_OPENGL_GLSL_INSTANTIATE_PROGRAM(\
	env\
)\
template class \
sge::opengl::glsl::program<\
	env\
>;

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_PROGRAM
)
