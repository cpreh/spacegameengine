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


#ifndef SGE_SPRITE_RENDER_RANGE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_IMPL_HPP_INCLUDED

#include <sge/sprite/render/range_decl.hpp>
#include <sge/sprite/render/range_part_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Choices
>
sge::sprite::render::range<
	Choices
>::range()
:
	object_(),
	range_parts_()
{
}

template<
	typename Choices
>
sge::sprite::render::range<
	Choices
>::range(
	range_object const &_object,
	range_part_vector &&_range_parts
)
:
	object_(
		_object
	),
	range_parts_(
		std::move(
			_range_parts
		)
	)
{
}

template<
	typename Choices
>
sge::sprite::render::range<
	Choices
>::range(
	range &&
)
= default;

template<
	typename Choices
>
sge::sprite::render::range<
	Choices
> &
sge::sprite::render::range<
	Choices
>::operator=(
	range &&
)
= default;

template<
	typename Choices
>
sge::sprite::render::range<
	Choices
>::~range()
{
}

template<
	typename Choices
>
typename
sge::sprite::render::range<
	Choices
>::optional_object const &
sge::sprite::render::range<
	Choices
>::object() const
{
	return
		object_;
}

template<
	typename Choices
>
typename
sge::sprite::render::range<
	Choices
>::range_part_vector const &
sge::sprite::render::range<
	Choices
>::parts() const
{
	return
		range_parts_;
}

#endif
