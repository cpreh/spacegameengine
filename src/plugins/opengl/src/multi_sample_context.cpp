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


#include <sge/opengl/multi_sample_context.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/glew/is_supported.hpp>

sge::opengl::multi_sample_context::multi_sample_context()
:
	is_native_(
		sge::opengl::glew::is_supported("GL_VERSION_1_3")
	),
	is_arb_(
		sge::opengl::glew::is_supported("GL_ARB_multisample")
	),
	flag_(
		static_cast<
			GLenum
		>(
			is_native_
			?
				GL_MULTISAMPLE
			:
				is_arb_
				?
					GL_MULTISAMPLE_ARB
				:
					0
		)
	)
{
}

sge::opengl::multi_sample_context::~multi_sample_context()
{
}

bool
sge::opengl::multi_sample_context::is_supported() const
{
	return
		is_native_
		|| is_arb_;
}

GLenum
sge::opengl::multi_sample_context::flag() const
{
	return flag_;
}

sge::opengl::context::id const
sge::opengl::multi_sample_context::static_id(
	sge::opengl::context::make_id()
);
