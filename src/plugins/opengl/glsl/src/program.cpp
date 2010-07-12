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
#include "../program_functions.hpp"
#include "../uniform/variable.hpp"
#include "../format_error.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/assert.hpp>

sge::opengl::glsl::program::program(
	opengl::context &_context,
	renderer::glsl::optional_string const &_vs_source,
	renderer::glsl::optional_string const &_ps_source
)
:
	instance_(
		_context
	),
	attachments_()
{
	FCPPT_ASSERT(
		vs_source || ps_source
	);

	if(
		vs_source
	)
		attach_shader(
			fcppt::make_shared_ptr<
				shader
			>(
				context().vertex_shader_type(),
				*_vs_source
			)
		);

	if(
		ps_source
	)
		attach_shader(
			fcppt::make_shared_ptr<
				shader_type
			>(
				context().pixel_shader_type(),
				*_ps_source
			)
		);

	link();
}

sge::opengl::glsl::program::~program()
{}

void
sge::opengl::glsl::program::use(
	renderer::glsl::program_ptr const _ptr
)
{
	if(
		!_ptr
	)
	{
		use_ffp();
		return;
	}

	fcppt::dynamic_pointer_cast<
		program
	>(
		_ptr
	)->use();
}

void
sge::opengl::glsl::program::attach_shader(
	shader_ptr const _shader
)
{
	typedef 
	fcppt::auto_ptr<
		attachment_type
	> attachment_auto_ptr
	
	attackment_auto_ptr ptr(
		fcppt::make_auto_ptr<
			attachment_type
		>(
			_shader,
			id()
		)
	);

	attachments_.push_back(
		ptr
	);
}

void
sge::opengl::glsl::program::link()
{
	context().link_program(
		id()
	);

	if(
		context.link_status(
			id()
		)
		== GL_FALSE
	)
		throw sge::renderer::glsl::exception(
			FCPPT_TEXT("Compiling a program failed:\n")
			+ info_log()
		);
}

void
sge::opengl::glsl::program::use()
{
	context().use_program(
		id()
	);
}

sge::renderer::glsl::uniform::variable_ptr const
sge::opengl::glsl::program::uniform(
	renderer::glsl::string const &_name
)
{
	return
		fcppt::make_shared_ptr<
			uniform::variable
		>(
			id(),
			_name
		);
}

fcppt::string const
sge::opengl::glsl::program::info_log() const
{
	return
		glsl::format_error(
			&context().program_info_log()
			&context().program_info_log_length(),
			id()
		);
}

void
sge::opengl::glsl::program::use_ffp()
{
	context().use_program(0);
}

sge::opengl::glsl::handle
sge::opengl::glsl::program::id() const
{
	return instance_.id();
}
