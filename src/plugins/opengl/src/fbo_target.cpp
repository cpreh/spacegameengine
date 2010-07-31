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


#include "../fbo_target.hpp"
#include "../bind_fbo.hpp"
#include "../fbo_context.hpp"
#include "../context/use.hpp"
#include <sge/renderer/texture.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sge::opengl::fbo_target::fbo_target(
	sge::opengl::context::object &_context,
	sge::renderer::parameters const &param_,
	opengl::texture_ptr const texture_
)
:
	context_(
		opengl::context::use<
			fbo_context
		>(
			_context
		)
	),
	fbo_(
		context_
	),
	texture_binding_(
		context_,
		texture_,
		fbo_
	)
{
}

sge::opengl::fbo_target::~fbo_target()
{
}

void
sge::opengl::fbo_target::bind() const
{
	fbo_.bind();
}

void
sge::opengl::fbo_target::unbind() const
{
	opengl::bind_fbo(
		context_,
		0
	);
}

sge::image::view::const_object const
sge::opengl::fbo_target::lock(
	renderer::lock_rect const &_dest
) const
{
	return
		texture_binding_.texture()->lock(
			_dest
		);
}

void
sge::opengl::fbo_target::unlock() const
{
	texture_binding_.texture()->unlock();
}

sge::renderer::target::dim_type const
sge::opengl::fbo_target::dim() const
{
	return texture_binding_.texture()->dim();
}
