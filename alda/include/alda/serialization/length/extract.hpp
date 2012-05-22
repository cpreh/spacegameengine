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


#ifndef ALDA_SERIALIZATION_LENGTH_EXTRACT_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_EXTRACT_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/serialization/istream.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/utility/enable_if.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{
namespace length
{

template<
	typename LengthType
>
typename boost::enable_if<
	boost::is_unsigned<
		LengthType
	>,
	fcppt::optional<
		LengthType
	>
>::type const
extract(
	alda::serialization::istream &_stream
)
{
	typedef fcppt::optional<
		LengthType
	> return_type;

	// in_avail can return showmanyc(), which can return -1
	return
		_stream.rdbuf()->in_avail()
		<
		static_cast<
			std::streamsize
		>(
			sizeof(
				LengthType
			)
		)
		?
			return_type()
		:
			fcppt::io::read<
				LengthType
			>(
				_stream,
				alda::endianness()
			);
}

}
}
}

#endif
