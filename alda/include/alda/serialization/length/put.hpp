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


#ifndef ALDA_SERIALIZATION_LENGTH_PUT_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_PUT_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/serialization/ostream.hpp>
#include <fcppt/static_assert_expression.hpp>
#include <fcppt/io/write.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/utility/enable_if.hpp>
#include <exception>
#include <limits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{
namespace length
{

template<
	typename LengthType,
	typename TypeEnum
>
typename boost::enable_if<
	boost::is_unsigned<
		LengthType
	>,
	void
>::type
put(
	alda::serialization::ostream &_stream,
	alda::message::base<
		TypeEnum
	> const &_message
)
{
	typedef alda::message::base<
		TypeEnum
	> message_base;

	typedef typename message_base::size_type message_size_type;

	FCPPT_STATIC_ASSERT_EXPRESSION(
		sizeof(
			message_size_type
		)
		>=
		sizeof(
			LengthType
		)
	);

	if(
		static_cast<
			message_size_type
		>(
			std::numeric_limits<
				LengthType
			>::max()
		)
		<=
		_message.size()
	)
		std::terminate();

	fcppt::io::write(
		_stream,
		static_cast<
			LengthType
		>(
			_message.size()
		),
		alda::endianness()
	);
}

}
}
}

#endif
