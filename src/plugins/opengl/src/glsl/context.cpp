/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/glew/is_supported.hpp>
#include <sge/opengl/glsl/context.hpp>
#include <sge/opengl/glsl/program_base.hpp>
#include <sge/renderer/glsl/const_optional_program_ref.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <fcppt/null_ptr.hpp>


sge::opengl::glsl::context::context()
:
	normal_shader_(
		glew::is_supported("GL_VERSION_2_0")
	),
	arb_shader_(
		glew::is_supported("GL_ARB_vertex_shader GL_ARB_fragment_shader")
	),
	last_program_(
		fcppt::null_ptr()
	)
{
}

sge::opengl::glsl::context::~context()
{
}

bool
sge::opengl::glsl::context::is_supported() const
{
	return
		normal_shader_
		|| arb_shader_;
}

bool
sge::opengl::glsl::context::is_native() const
{
	return normal_shader_;
}

void
sge::opengl::glsl::context::use(
	sge::renderer::glsl::const_optional_program_ref const &_prog
)
{
	if(
		last_program_
	)
		last_program_->unuse();

	last_program_ = fcppt::null_ptr();

	if(
		!_prog
	)
		return;

	glsl::program_base const &prog_base(
		dynamic_cast<
			glsl::program_base const &
		>(
			*_prog
		)
	);

	prog_base.use();

	last_program_ = &prog_base;
}

sge::opengl::context::id const
sge::opengl::glsl::context::static_id(
	sge::opengl::context::make_id()
);
