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


#ifndef SGE_SPRITE_INTRUSIVE_CONNECTION_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_CONNECTION_IMPL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/intrusive/connection_decl.hpp>


template<
	typename Choices
>
sge::sprite::intrusive::connection<
	Choices
>::connection(
	list &_list,
	sge::sprite::count &_count
)
:
	list_(
		_list
	),
	count_(
		_count
	)
{
}

template<
	typename Choices
>
sge::sprite::intrusive::connection<
	Choices
>::~connection()
{
}

template<
	typename Choices
>
void
sge::sprite::intrusive::connection<
	Choices
>::add(
	object &_sprite
)
{
	list_.push_back(
		_sprite
	);

	++count_;
}

template<
	typename Choices
>
void
sge::sprite::intrusive::connection<
	Choices
>::remove()
{
	--count_;
}

#endif
