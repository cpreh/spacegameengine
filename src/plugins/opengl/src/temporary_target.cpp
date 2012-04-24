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


#include <sge/opengl/temporary_target.hpp>
#include <sge/opengl/target_base.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/fbo/bind.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/no_buffer.hpp>
#include <sge/opengl/fbo/unbind.hpp>


sge::opengl::temporary_target::temporary_target(
	sge::opengl::context::object &_context,
	sge::opengl::target_base &_target
)
:
	fbo_context_(
		sge::opengl::context::use<
			sge::opengl::fbo::context
		>(
			_context
		)
	),
	target_(
		_target
	),
	previous_fbo_(
		fbo_context_.last_buffer()
	)
{
	if(
		target_.active()
	)
		return;

	if(
		previous_fbo_
		!=
		sge::opengl::fbo::no_buffer()
	)
		sge::opengl::fbo::unbind(
			fbo_context_
		);

	target_.bind();
}

sge::opengl::temporary_target::~temporary_target()
{
	if(
		target_.active()
	)
		return;

	target_.unbind();

	if(
		previous_fbo_
		!=
		sge::opengl::fbo::no_buffer()
	)
		sge::opengl::fbo::bind(
			fbo_context_,
			previous_fbo_
		);
}
