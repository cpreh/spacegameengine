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


#ifndef SGE_SPRITE_RENDER_RANGE_PART_IMPL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_PART_IMPL_HPP_INCLUDED

#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/roles/index_count.hpp>
#include <sge/sprite/detail/roles/texture.hpp>
#include <sge/sprite/detail/roles/vertex_count.hpp>
#include <sge/sprite/render/range_part_decl.hpp>


template<
	typename Choices
>
sge::sprite::render::range_part<
	Choices
>::range_part(
	range_part_object const &_object
)
:
	object_(
		_object
	)
{
}

template<
	typename Choices
>
sge::renderer::index::first const
sge::sprite::render::range_part<
	Choices
>::first_index() const
{
	return
		object_. template get<
			sge::sprite::buffers::roles::first_index
		>();
}

template<
	typename Choices
>
sge::renderer::vertex::first const
sge::sprite::render::range_part<
	Choices
>::first_vertex() const
{
	return
		object_. template get<
			sge::sprite::buffers::roles::first_vertex
		>();
}

template<
	typename Choices
>
sge::renderer::vertex::count const
sge::sprite::render::range_part<
	Choices
>::vertex_count() const
{
	return
		object_. template get<
			sge::sprite::detail::roles::vertex_count
		>();
}

template<
	typename Choices
>
sge::renderer::index::count const
sge::sprite::render::range_part<
	Choices
>::index_count() const
{
	return
		object_. template get<
			sge::sprite::detail::roles::index_count
		>();
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
sge::renderer::texture::planar const *
sge::sprite::render::range_part<
	Choices
>::texture_level() const
{
	return
		object_. template get<
			sge::sprite::detail::roles::texture<
				Level
			>
		>();
}

#endif
