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


#ifndef ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include <alda/bindings/detail/extract_length.hpp>
#include <alda/bindings/detail/put_length.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
struct dynamic_len
{
	typedef Type type;

	typedef boost::uint16_t length_type;
};

template<
	typename Type,
	typename Adapted
>
majutsu::size_type
needed_size(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::dynamic_len<
		Type,
		Adapted
	> const *,
	Type const &_value
)
{
	majutsu::size_type ret(
		sizeof(
			typename alda::bindings::dynamic_len<
				Type,
				Adapted
			>::length_type
		)
	);

	for(
		typename Type::const_iterator elem_it(
			_value.begin()
		);
		elem_it != _value.end();
		++elem_it
	)
		ret +=
			needed_size(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				*elem_it
			);

	return ret;
}

template<
	typename Type,
	typename Adapted
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::dynamic_len<
		Type,
		Adapted
	> const *const _concept,
	Type const &_value,
	majutsu::raw_pointer _mem
)
{
	alda::bindings::detail::put_length(
		_tag,
		_concept,
		_value,
		_mem
	);

	for(
		typename Type::const_iterator it(
			_value.begin()
		);
		it != _value.end();
		_mem +=
			needed_size(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				*it
			),
		++it
	)
		place(
			_tag,
			static_cast<
				Adapted const *
			>(0),
			*it,
			_mem
		);
}

template<
	typename Type,
	typename Adapted
>
Type
make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::dynamic_len<
		Type,
		Adapted
	> const *const _concept,
	majutsu::const_raw_pointer const _mem
)
{
	typedef typename alda::bindings::dynamic_len<
		Type,
		Adapted
	>::length_type length_type;

	length_type const my_size(
		alda::bindings::detail::extract_length(
			_tag,
			_concept,
			_mem
		)
	);

	Type ret;

	for(
		majutsu::const_raw_pointer cur_mem(
			_mem + sizeof(length_type)
		);
		cur_mem != _mem + my_size;
	)
	{
		typename Type::value_type elem(
			make(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				cur_mem
			)
		);

		ret.push_back(
			elem
		);

		cur_mem +=
			needed_size(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				elem
			);
	}

	return ret;
}

}
}

#endif
