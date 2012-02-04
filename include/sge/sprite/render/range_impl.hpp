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


#ifndef SGE_SPRITE_RENDER_RANGE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_IMPL_HPP_INCLUDED

#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/sprite/buffers/roles/index_buffer.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/render/range_decl.hpp>
#include <sge/sprite/render/range_part_impl.hpp>
#include <fcppt/null_ptr.hpp>


template<
	typename Choices
>
sge::sprite::render::range<
	Choices
>::range()
:
	range_parts_(
		fcppt::null_ptr()
	),
	object_()
{
}

template<
	typename Choices
>
sge::sprite::render::range<
	Choices
>::range(
	range_part_vector &_range_parts,
	range_object const &_object
)
:
	range_parts_(
		&_range_parts
	),
	object_(
		_object
	)
{
}

template<
	typename Choices
>
void
sge::sprite::render::range<
	Choices
>::add(
	range_part_type const &_part
)
{
	range_parts_->push_back(
		_part
	);
}

template<
	typename Choices
>
typename sge::sprite::render::range<
	Choices
>::const_iterator
sge::sprite::render::range<
	Choices
>::begin() const
{
	return
		range_parts_->begin();
}

template<
	typename Choices
>
typename sge::sprite::render::range<
	Choices
>::const_iterator
sge::sprite::render::range<
	Choices
>::end() const
{
	return
		range_parts_->end();
}

template<
	typename Choices
>
sge::renderer::vertex_buffer const &
sge::sprite::render::range<
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
sge::renderer::index_buffer const &
sge::sprite::render::range<
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
bool
sge::sprite::render::range<
	Choices
>::empty() const
{
	return
		!range_parts_
		||
		range_parts_->empty();
}

#endif
