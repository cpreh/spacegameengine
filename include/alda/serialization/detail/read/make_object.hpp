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


#ifndef ALDA_SERIALIZATION_DETAIL_READ_MAKE_OBJECT_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_MAKE_OBJECT_HPP_INCLUDED

#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/read/element_impl.hpp>
#include <majutsu/is_role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/placeholders.hpp>
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
	typename Message
>
Message const
make_object(
	alda::serialization::istream &_stream
)
{
	Message obj;

	boost::mpl::for_each<
		boost::mpl::filter_view<
			typename Message::memory_type::types,
			majutsu::is_role<
				boost::mpl::_1
			>
		>
	>(
		alda::serialization::detail::read::element<
			Message
		>(
			_stream,
			obj
		)
	);

	return obj;
}

}
}
}
}

#endif
