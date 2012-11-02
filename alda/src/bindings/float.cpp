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


#include <alda/bindings/float.hpp>
#include <alda/bindings/fundamental.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef boost::uint32_t fixed_int;

typedef alda::bindings::float_::type float_type;

typedef alda::bindings::fundamental<
	fixed_int
> adapted;

fixed_int const sign_bit(
	0x1u
);

float_type const exp(
	static_cast<
		float_type
	>(
		1ul << 16
	)
);

fixed_int
make_fixed(
	float_type const _val
)
{
	return
		static_cast<
			fixed_int
		>(
			std::log(
				_val
				+
				static_cast<
					float_type
				>(
					1
				)
			)
			* exp
		);
}

float_type
unmake_fixed(
	fixed_int const _val
)
{
	return
		std::exp(
			static_cast<
				float_type
			>(
				_val
			)
			/ exp
		)
		- static_cast<
			float_type
		>(
			1
		);
}

fixed_int
serialize(
	float_type const _val
)
{
	return
		_val < 0
		?
			make_fixed(
				-_val
			)
			| sign_bit
		:
			make_fixed(
				_val
			)
			& ~sign_bit;
}

float_type
deserialize(
	fixed_int _val
)
{
	bool const is_signed(
		_val & sign_bit
	);

	_val &= ~sign_bit;

	return
		is_signed
		?
			unmake_fixed(
				_val
			)
			* static_cast<
				float_type
			>(
				-1
			)
		:
			unmake_fixed(
				_val
			);
}

}

majutsu::size_type
alda::bindings::needed_size(
	majutsu::concepts::dynamic_memory::tag const *,
	alda::bindings::float_ const *,
	alda::bindings::float_::type const &
)
{
	return sizeof(fixed_int);
}

void
alda::bindings::place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::float_ const *,
	alda::bindings::float_::type const &_val,
	majutsu::raw_pointer const _mem
)
{
	place(
		_tag,
		static_cast<
			adapted const *
		>(0),
		serialize(
			_val
		),
		_mem
	);
}

alda::bindings::float_::type
alda::bindings::make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::float_ const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		deserialize(
			make(
				_tag,
				static_cast<
					adapted const *
				>(0),
				_beg
			)
		);
}
