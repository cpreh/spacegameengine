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


#ifndef ALDA_SERIALIZATION_DETAIL_READ_LOAD_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_LOAD_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/bindings/dynamic_len.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/raw_container.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{
namespace read
{

template<
	typename Type
>
struct load
{
	static typename Type::type
	get(
		alda::serialization::istream &_is
	)
	{
		typename Type::type ret;

		alda::serialization::detail::raw_container vec(
			// ADL call
			needed_size(
				static_cast<
					majutsu::concepts::dynamic_memory::tag const *
				>(0),
				static_cast<
					Type const *
				>(0),
				ret
			)
		);

		_is.read(
			reinterpret_cast<
				char *
			>(
				vec.data()
			),
			static_cast<
				std::streamsize
			>(
				vec.size()
			)
		);

		return
			// ADL call
			make(
				static_cast<
					majutsu::concepts::dynamic_memory::tag const *
				>(0),
				static_cast<
					Type const *
				>(0),
				vec.data()
			);
	}
};

template<
	typename T,
	typename A
>
struct load<
	alda::bindings::dynamic_len<
		T,
		A
	>
>
{
	static typename alda::bindings::dynamic_len<T, A>::type
	get(
		alda::serialization::istream &_is
	)
	{
		typedef alda::bindings::dynamic_len<T, A> type;

		typename type::type ret;

		majutsu::size_type const length_sz(
			sizeof(typename type::length_type)
		);

		typedef typename type::length_type length_type;

		// At this point, the stream must be able to read its length
		length_type const sz(
			*fcppt::io::read<
				length_type
			>(
				_is,
				alda::endianness()
			)
		);

		raw_container vec(
			sz + length_sz
		);

		fcppt::algorithm::copy_n(
			reinterpret_cast<
				raw_container::const_pointer
			>(
				&sz
			),
			sizeof(length_type),
			vec.data()
		);

		_is.read(
			reinterpret_cast<
				char *
			>(
				vec.data()
				+
				length_sz
			),
			static_cast<
				std::streamsize
			>(
				sz - length_sz
			)
		);

		return
			// ADL call
			make(
				static_cast<
					majutsu::concepts::dynamic_memory::tag const *
				>(0),
				static_cast<
					type const *
				>(0),
				vec.data()
			);
	}
};

}
}
}
}

#endif
