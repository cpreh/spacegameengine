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


#ifndef SGE_SPRITE_BUFFERS_SLICE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SLICE_IMPL_HPP_INCLUDED

#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/buffers/slice_decl.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/buffers/roles/index_buffer.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <majutsu/get.hpp>


template<
	typename Choices
>
sge::sprite::buffers::slice<
	Choices
>::slice(
	object_ref const _object,
	offset_object const _offsets
)
:
	object_(
		_object
	),
	offsets_(
		_offsets
	)
{
}

template<
	typename Choices
>
sge::renderer::vertex::buffer &
sge::sprite::buffers::slice<
	Choices
>::vertex_buffer() const
{
	return
		*majutsu::get<
			sge::sprite::buffers::roles::vertex_buffer
		>(
			this->buffer_object()
		);
}

template<
	typename Choices
>
sge::renderer::index::buffer &
sge::sprite::buffers::slice<
	Choices
>::index_buffer() const
{
	return
		*majutsu::get<
			sge::sprite::buffers::roles::index_buffer
		>(
			this->buffer_object()
		);
}

template<
	typename Choices
>
sge::renderer::vertex::first
sge::sprite::buffers::slice<
	Choices
>::first_vertex() const
{
	return
		majutsu::get<
			sge::sprite::buffers::roles::first_vertex
		>(
			offsets_
		);
}

template<
	typename Choices
>
sge::renderer::index::first
sge::sprite::buffers::slice<
	Choices
>::first_index() const
{
	return
		majutsu::get<
			sge::sprite::buffers::roles::first_index
		>(
			offsets_
		);
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
	return
		object_.get();
}

#endif
