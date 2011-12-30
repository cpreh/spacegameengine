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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/assert/pre.hpp>


sge::opengl::texture::render_binding::render_binding(
	sge::opengl::context::object &_context,
	sge::renderer::texture::stage const &_stage
)
{
	FCPPT_ASSERT_PRE(
		sge::opengl::context::use<
			sge::opengl::texture::bind_context
		>(
			_context
		).render_texture(
			_stage
		)
		!=
		fcppt::null_ptr()
	);
}

sge::opengl::texture::render_binding::~render_binding()
{
}
