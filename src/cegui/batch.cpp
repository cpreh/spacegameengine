/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/src/cegui/batch.hpp>
#include <sge/src/cegui/clip.hpp>


sge::cegui::batch::batch(
	sge::renderer::device::core &_renderer,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::renderer::texture::planar &_texture,
	sge::renderer::vertex::count const _vertex_count,
	sge::cegui::clip const _clip
)
:
	texture_(
		_texture
	),
	vertex_buffer_(
		_renderer.create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				_vertex_declaration,
				sge::renderer::vf::dynamic::part_index(
					0u
				),
				_vertex_count,
				sge::renderer::resource_flags_field::null()
			)
		)
	),
	clip_(
		_clip
	)
{
}

sge::cegui::batch::batch(
	batch &&
) = default;

sge::cegui::batch &
sge::cegui::batch::operator=(
	batch &&
) = default;

sge::cegui::batch::~batch()
{
}

sge::renderer::texture::planar &
sge::cegui::batch::texture() const
{
	return
		texture_.get();
}

sge::renderer::vertex::buffer &
sge::cegui::batch::vertex_buffer() const
{
	return
		*vertex_buffer_;
}

sge::cegui::clip
sge::cegui::batch::clip() const
{
	return
		clip_;
}
