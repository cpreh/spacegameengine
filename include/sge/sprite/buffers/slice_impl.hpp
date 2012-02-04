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


#ifndef SGE_SPRITE_BUFFERS_SLICE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SLICE_IMPL_HPP_INCLUDED

#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/sprite/buffers/slice_decl.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/buffers/roles/index_buffer.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/render/range_part_impl.hpp>


template<
	typename Choices
>
sge::sprite::buffers::slice<
	Choices
>::slice(
	object const &_object,
	offset_object const &_offset_object
)
:
	object_(
		_object
	),
	offset_object_(
		_offset_object
	),
	part_vector_()
{
}

template<
	typename Choices
>
sge::sprite::buffers::slice<
	Choices
>::~slice()
{
}

template<
	typename Choices
>
sge::renderer::vertex_buffer &
sge::sprite::buffers::slice<
	Choices
>::vertex_buffer() const
{
	return
		*object_. template get<
			sge::sprite::buffers::roles::vertex_buffer
		>();
}

template<
	typename Choices
>
sge::renderer::index_buffer &
sge::sprite::buffers::slice<
	Choices
>::index_buffer() const
{
	return
		*object_. template get<
			sge::sprite::buffers::roles::index_buffer
		>();
}

template<
	typename Choices
>
sge::renderer::first_vertex const
sge::sprite::buffers::slice<
	Choices
>::first_vertex() const
{
	return
		offset_object_. template get<
			sge::sprite::buffers::roles::first_vertex
		>();
}

template<
	typename Choices
>
sge::renderer::first_index const
sge::sprite::buffers::slice<
	Choices
>::first_index() const
{
	return
		offset_object_. template get<
			sge::sprite::buffers::roles::first_index
		>();
}

template<
	typename Choices
>
typename sge::sprite::buffers::slice<
	Choices
>::range_part_vector &
sge::sprite::buffers::slice<
	Choices
>::part_vector()
{
	return part_vector_;
}

template<
	typename Choices
>
typename sge::sprite::buffers::slice<
	Choices
>::object const &
sge::sprite::buffers::slice<
	Choices
>::buffer_object() const
{
	return object_;
}

template<
	typename Choices
>
void
sge::sprite::buffers::slice<
	Choices
>::reset(
	object const &_object,
	offset_object const &_offset_object
)
{
	object_ = _object;

	offset_object_ = _offset_object;

	part_vector_.clear();
}

#endif
