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


#include <sge/renderer/const_vertex_buffer_ref_container.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/sprite/detail/render/scoped_vertex.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/assign/make_container.hpp>


sge::sprite::detail::render::scoped_vertex<
	sge::sprite::render::vertex_options::nothing
>::scoped_vertex(
	sge::renderer::device &,
	sge::renderer::vertex_declaration const &,
	sge::renderer::vertex_buffer const &
)
{
}

sge::sprite::detail::render::scoped_vertex<
	sge::sprite::render::vertex_options::nothing
>::~scoped_vertex()
{
}

sge::sprite::detail::render::scoped_vertex<
	sge::sprite::render::vertex_options::declaration
>::scoped_vertex(
	sge::renderer::device &_device,
	sge::renderer::vertex_declaration const &_vertex_declaration,
	sge::renderer::vertex_buffer const &
)
:
	vertex_declaration_(
		_device,
		_vertex_declaration
	)
{
}

sge::sprite::detail::render::scoped_vertex<
	sge::sprite::render::vertex_options::declaration
>::~scoped_vertex()
{
}

sge::sprite::detail::render::scoped_vertex<
	sge::sprite::render::vertex_options::buffer
>::scoped_vertex(
	sge::renderer::device &_device,
	sge::renderer::vertex_declaration const &,
	sge::renderer::vertex_buffer const &_vertex_buffer
)
:
	vertex_buffer_(
		_device,
		_vertex_buffer
	)
{
}

sge::sprite::detail::render::scoped_vertex<
	sge::sprite::render::vertex_options::buffer
>::~scoped_vertex()
{
}

sge::sprite::detail::render::scoped_vertex<
	sge::sprite::render::vertex_options::declaration_and_buffer
>::scoped_vertex(
	sge::renderer::device &_device,
	sge::renderer::vertex_declaration const &_vertex_declaration,
	sge::renderer::vertex_buffer const &_vertex_buffer
)
:
	vertex_declaration_and_buffers_(
		_device,
		_vertex_declaration,
		fcppt::assign::make_container<
			sge::renderer::const_vertex_buffer_ref_container
		>(
			fcppt::cref(
				_vertex_buffer
			)
		)
	)
{
}

sge::sprite::detail::render::scoped_vertex<
	sge::sprite::render::vertex_options::declaration_and_buffer
>::~scoped_vertex()
{
}
