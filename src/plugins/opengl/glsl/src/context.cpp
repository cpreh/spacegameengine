/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../context.hpp"
#include "../program_base.hpp"
#include "../../glew/is_supported.hpp"
#include "../../context/make_id.hpp"
#include <sge/renderer/glsl/program.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>

sge::opengl::glsl::context::context()
:
	normal_shader_(
		glew::is_supported("GL_VERSION_2_0")
	),
	arb_shader_(
		glew::is_supported("GL_ARB_vertex_shader GL_ARB_fragment_shader")
	),
	last_program_()
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
	sge::renderer::glsl::const_program_ptr const _prog
)
{
	typedef fcppt::shared_ptr<
		program_base const
	> program_base_ptr;

	if(
		!_prog
	)
	{
		program_base_ptr const locked(
			last_program_.lock()
		);

		if(
			locked
		)
			locked->unuse();
	}
	else
	{
		program_base_ptr const base(
			fcppt::dynamic_pointer_cast<
				program_base const
			>(
				_prog
			)
		);

		base->use();

		last_program_ = base;
	}
}

sge::opengl::glsl::const_program_base_ptr const
sge::opengl::glsl::context::active_program() const
{
	return last_program_.lock();
}

sge::opengl::context::id const
sge::opengl::glsl::context::static_id(
	sge::opengl::context::make_id()
);
