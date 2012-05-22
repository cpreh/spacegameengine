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


#ifndef ALDA_SERIALIZATION_LENGTH_DESERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_DESERIALIZE_HPP_INCLUDED

#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/length/extract.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/utility/enable_if.hpp>
#include <ostream>
#include <iosfwd>
#include <cstddef>
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
	typename alda::message::base_unique_ptr<
		TypeEnum
	>::type
>::type
deserialize(
	alda::serialization::context<
		TypeEnum
	> const &_context,
	alda::serialization::istream &_stream
)
{
	typedef fcppt::optional<
		LengthType
	> length_result;

	length_result const length(
		alda::serialization::length::extract<
			LengthType
		>(
			_stream
		)
	);

	typedef typename alda::message::base_unique_ptr<
		TypeEnum
	>::type result_type;

	if(
		!length
	)
		return
			result_type();

	if(
		// in_avail can return -1
		_stream.rdbuf()->in_avail()
		<
		static_cast<
			std::streamsize
		>(
			*length
		)
	)
	{
		// TODO: should be putback the length instead?
		for(
			std::size_t i = 0;
			i < sizeof(LengthType);
			++i
		)
			_stream.unget();

		return
			result_type();
	}

	return
		alda::serialization::deserialize(
			_context,
			_stream
		);
}

}
}
}

#endif
