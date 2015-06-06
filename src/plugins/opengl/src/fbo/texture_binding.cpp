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


#include <sge/opengl/fbo/attach_texture_2d.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/texture_binding.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/id.hpp>


sge::opengl::fbo::texture_binding::texture_binding(
	sge::opengl::fbo::config const &_context,
	sge::opengl::texture::buffer_base &_buffer,
	sge::opengl::fbo::attachment_type const _attachment
)
:
	context_(
		_context
	),
	buffer_(
		_buffer
	),
	attachment_(
		_attachment
	)
{
	sge::opengl::fbo::attach_texture_2d(
		_context,
		_attachment,
		_buffer.buffer_type(),
		_buffer.id(),
		_buffer.level()
	);
}

sge::opengl::fbo::texture_binding::~texture_binding()
{
	sge::opengl::fbo::attach_texture_2d(
		context_,
		attachment_,
		buffer_.buffer_type(),
		sge::opengl::texture::id(
			0u
		),
		buffer_.level()
	);
}
