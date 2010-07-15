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


#include "../program.hpp"
#include "../attachment.hpp"
#include "../format_error.hpp"
#include "../uniform/variable.hpp"
#include "../programfuncs/create.hpp"
#include "../programfuncs/delete.hpp"
#include "../programfuncs/link.hpp"
#include "../programfuncs/link_status.hpp"
#include "../programfuncs/info_log.hpp"
#include "../programfuncs/info_log_length.hpp"
#include "../programfuncs/use.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_auto_ptr.hpp>

template<
	typename Environment
>
sge::opengl::glsl::program<Environment>::program(
	opengl::context::object &_context
)
:
	context_(
		opengl::context::use<
			typename Environment::program_context
		>(
			_context
		)
	),
	id_(
		programfuncs::create<
			Environment
		>(
			context_
		)
	),
	vertex_shader_(),
	pixel_shader_()
{}

template<
	typename Environment
>
sge::opengl::glsl::program<Environment>::~program()
{
	programfuncs::delete_<
		Environment
	>(
		context_,
		id_
	);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::use()
{
	do_use(
		id()
	);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::unuse()
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
			id(),
			_name
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
sge::opengl::glsl::program<Environment>::vertex_shader(
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
sge::opengl::glsl::program<Environment>::link()
{
	programfuncs::link<
		Environment
	>(
		context_,
		id_
	);

	if(
		programfuncs::link_status<
			Environment
		>(
			context_,
			id_
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
			programfuncs::info_log<
				Environment
			>(
				context_,
				id_
			),
			programfuncs::info_log_length<
				Environment
			>(
				context_,
				id_
			),
			id_
		);
}

template<
	typename Environment
>
void
sge::opengl::glsl::program<Environment>::do_use(
	handle const handle_
)
{
	programfuncs::use<
		Environment
	>(
		context_,
		handle_
	);
}

template<
	typename Environment
>
typename sge::opengl::glsl::program<Environment>::attachment_auto_ptr
sge::opengl::glsl::program::make_attachment(
	sge::renderer::glsl::shader_ptr const _shader
)
{
	attachment_auto_ptr ptr(
		fcppt::make_auto_ptr<
			attachment_type
		>(
			_shader,
			id()
		)
	);

	return ret;
}
