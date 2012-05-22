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


#ifndef ALDA_SERIALIZATION_LENGTH_SERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_SERIALIZE_HPP_INCLUDED

#include <alda/message/base_fwd.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/serialize.hpp>
#include <alda/serialization/length/put.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/utility/enable_if.hpp>
#include <ostream>
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
serialize(
	alda::serialization::ostream &_stream,
	alda::message::base<
		TypeEnum
	> const &_message
)
{
	alda::serialization::length::put<
		LengthType
	>(
		_stream,
		_message
	);

	alda::serialization::serialize(
		_stream,
		_message
	);
}

}
}
}

#endif
