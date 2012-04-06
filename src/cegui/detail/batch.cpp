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


#include <sge/cegui/detail/batch.hpp>
#include <sge/renderer/vertex_buffer_shared_ptr.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>


sge::cegui::detail::batch::batch(
	sge::renderer::texture::planar &_texture,
	sge::renderer::vertex_buffer_shared_ptr const _vertex_buffer
)
:
	texture_(
		&_texture
	),
	vertex_buffer_(
		_vertex_buffer
	)
{
}

sge::cegui::detail::batch::batch(
	batch const &_other
)
:
	texture_(
		_other.texture_
	),
	vertex_buffer_(
		_other.vertex_buffer_
	)
{
}

sge::cegui::detail::batch &
sge::cegui::detail::batch::operator=(
	batch const &_other
)
{
	if(
		this == &_other
	)
		return *this;

	texture_ = _other.texture_;

	vertex_buffer_ = _other.vertex_buffer_;

	return *this;
}

sge::cegui::detail::batch::~batch()
{
}

sge::renderer::texture::planar &
sge::cegui::detail::batch::texture() const
{
	return *texture_;
}

sge::renderer::vertex_buffer &
sge::cegui::detail::batch::vertex_buffer() const
{
	return *vertex_buffer_;
}
