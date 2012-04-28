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


#include <sge/cg/check_state.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/opengl/cg/program/loaded_object.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::cg::program::loaded_object::loaded_object(
	sge::cg::program::object &_program
)
:
	program_(
		_program
	)
{
	::cgGLLoadProgram(
		program_.get()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGLLoadProgram failed"),
		sge::renderer::exception
	)
}

sge::opengl::cg::program::loaded_object::~loaded_object()
{
	::cgGLUnloadProgram(
		program_.get()
	);
}

void
sge::opengl::cg::program::loaded_object::activate() const
{
	{
		::cgGLBindProgram(
			program_.get()
		);

		SGE_CG_CHECK_STATE(
			FCPPT_TEXT("cgGLBindProgram"),
			sge::renderer::exception
		)
	}

	{
		::cgGLEnableProfile(
			program_.profile().get()
		);

		SGE_CG_CHECK_STATE(
			FCPPT_TEXT("cgGLEnableProfile"),
			sge::renderer::exception
		)
	}
}

void
sge::opengl::cg::program::loaded_object::deactivate() const
{
	{
		::cgGLDisableProfile(
			program_.profile().get()
		);

		SGE_CG_CHECK_STATE(
			FCPPT_TEXT("cgGLDisableProfile"),
			sge::renderer::exception
		)
	}

	{
		::cgGLUnbindProgram(
			program_.profile().get()
		);

		SGE_CG_CHECK_STATE(
			FCPPT_TEXT("cgGLUnbindProgram"),
			sge::renderer::exception
		)
	}
}
