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


#ifndef ALDA_SERIALIZATION_SERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_SERIALIZE_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <alda/serialization/ostream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{

template<
	typename TypeEnum
>
void
serialize(
	alda::serialization::ostream &_stream,
	alda::message::base<
		TypeEnum
	> const &_message
)
{
	_stream.write(
		reinterpret_cast<
			alda::serialization::ostream::char_type const *
		>(
			_message.data()
		),
		static_cast<
			std::streamsize
		>(
			_message.size()
		)
	);
}

}
}

#endif
