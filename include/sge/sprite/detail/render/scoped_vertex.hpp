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


#ifndef SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_HPP_INCLUDED

#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_declaration_and_buffers.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/sprite/buffers/parameters_fwd.hpp>
#include <sge/sprite/symbol.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	sge::sprite::render::vertex_options::type Options
>
class scoped_vertex;

template<>
class scoped_vertex<
	sge::sprite::render::vertex_options::nothing
>
{
	FCPPT_NONCOPYABLE(
		scoped_vertex
	);
public:
	SGE_SPRITE_SYMBOL
	scoped_vertex(
		sge::sprite::buffers::parameters const &,
		sge::renderer::vertex_buffer const &
	);

	SGE_SPRITE_SYMBOL
	~scoped_vertex();
};

template<>
class scoped_vertex<
	sge::sprite::render::vertex_options::declaration
>
{
	FCPPT_NONCOPYABLE(
		scoped_vertex
	);
public:
	SGE_SPRITE_SYMBOL
	scoped_vertex(
		sge::sprite::buffers::parameters const &,
		sge::renderer::vertex_buffer const &
	);

	SGE_SPRITE_SYMBOL
	~scoped_vertex();
private:
	sge::renderer::scoped_vertex_declaration const vertex_declaration_;
};

template<>
class scoped_vertex<
	sge::sprite::render::vertex_options::buffer
>
{
	FCPPT_NONCOPYABLE(
		scoped_vertex
	);
public:
	SGE_SPRITE_SYMBOL
	scoped_vertex(
		sge::sprite::buffers::parameters const &,
		sge::renderer::vertex_buffer const &
	);

	SGE_SPRITE_SYMBOL
	~scoped_vertex();
private:
	sge::renderer::scoped_vertex_buffer const vertex_buffer_;
};

template<>
class scoped_vertex<
	sge::sprite::render::vertex_options::declaration_and_buffer
>
{
	FCPPT_NONCOPYABLE(
		scoped_vertex
	);
public:
	SGE_SPRITE_SYMBOL
	scoped_vertex(
		sge::sprite::buffers::parameters const &,
		sge::renderer::vertex_buffer const &
	);

	SGE_SPRITE_SYMBOL
	~scoped_vertex();
private:
	sge::renderer::scoped_vertex_declaration_and_buffers const vertex_declaration_and_buffers_;
};

}
}
}
}

#endif
