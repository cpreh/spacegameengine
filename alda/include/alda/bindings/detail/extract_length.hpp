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


#ifndef ALDA_BINDINGS_DETAIL_EXTRACT_LENGTH_HPP_INCLUDED
#define ALDA_BINDINGS_DETAIL_EXTRACT_LENGTH_HPP_INCLUDED

#include <alda//endianness.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/endianness/convert.hpp>


namespace alda
{
namespace bindings
{
namespace detail
{

template<
	typename Concept
>
typename Concept::length_type
extract_length(
	majutsu::concepts::dynamic_memory::tag const *,
	Concept const *,
	majutsu::const_raw_pointer const _memory
)
{
	typedef typename Concept::length_type length_type;

	length_type ret;

	fcppt::algorithm::copy_n(
		_memory,
		sizeof(length_type),
		reinterpret_cast<
			majutsu::raw_pointer
		>(
			&ret
		)
	);

	return
		fcppt::endianness::convert(
			ret,
			alda::endianness()
		);
}

}
}
}

#endif
