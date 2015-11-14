/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/pixel_store_context.hpp>
#include <sge/opengl/pixel_store_int.hpp>
#include <sge/opengl/set_unpack_alignment.hpp>
#include <sge/opengl/unpack_alignment.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>


void
sge::opengl::set_unpack_alignment(
	sge::opengl::context::object &_context,
	sge::opengl::unpack_alignment const _alignment
)
{
	sge::opengl::pixel_store_context &context(
		sge::opengl::context::use<
			sge::opengl::pixel_store_context
		>(
			_context
		)
	);

	if(
		context.unpack_alignment()
		==
		_alignment
	)
		return;

	sge::opengl::pixel_store_int(
		GL_UNPACK_ALIGNMENT,
		_alignment.get()
	);

	context.unpack_alignment(
		_alignment
	);
}
