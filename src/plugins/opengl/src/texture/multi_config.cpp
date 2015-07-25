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


#include <sge/opengl/texture/multi_config.hpp>
#include <sge/renderer/caps/texture_stages.hpp>


sge::opengl::texture::multi_config::multi_config(
	gl_active_texture _active_texture,
	gl_client_active_texture _client_active_texture,
	sge::renderer::caps::texture_stages const _max_level
)
:
	active_texture_(
		_active_texture
	),
	client_active_texture_(
		_client_active_texture
	),
	max_level_(
		_max_level
	)
{
}

sge::opengl::texture::multi_config::gl_active_texture
sge::opengl::texture::multi_config::active_texture() const
{
	return
		active_texture_;
}

sge::opengl::texture::multi_config::gl_client_active_texture
sge::opengl::texture::multi_config::client_active_texture() const
{
	return
		client_active_texture_;
}

sge::renderer::caps::texture_stages const
sge::opengl::texture::multi_config::max_level() const
{
	return
		max_level_;
}
