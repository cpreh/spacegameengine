//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <fcppt/record/get.hpp>


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
		*fcppt::record::get<
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
		*fcppt::record::get<
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
		fcppt::record::get<
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
		fcppt::record::get<
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
