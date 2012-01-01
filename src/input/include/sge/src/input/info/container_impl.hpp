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


#ifndef SGE_SRC_INPUT_INFO_CONTAINER_IMPL_HPP_INCLUDED
#define SGE_SRC_INPUT_INFO_CONTAINER_IMPL_HPP_INCLUDED

#include <sge/input/info/container.hpp>

template<
	typename Id,
	typename Obj
>
sge::input::info::container<
	Id,
	Obj
>::container(
	vector const &_vector
)
:
	vector_(
		_vector
	)
{
}

template<
	typename Id,
	typename Obj
>
Obj const &
sge::input::info::container<
	Id,
	Obj
>::operator[](
	Id const &_id
) const
{
	return
		vector_[
			_id.get()
		];
}

template<
	typename Id,
	typename Obj
>
Id const
sge::input::info::container<
	Id,
	Obj
>::size() const
{
	return
		Id(
			static_cast<
				typename Id::value_type
			>(
				vector_.size()
			)
		);
}

template<
	typename Id,
	typename Obj
>
typename sge::input::info::container<
	Id,
	Obj
>::vector const &
sge::input::info::container<
	Id,
	Obj
>::get() const
{
	return vector_;
}

#endif
