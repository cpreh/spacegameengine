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


#ifndef SGE_SPRITE_DETAIL_DEFAULT_INITIALIZE_CLASS_ELEMENT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_DEFAULT_INITIALIZE_CLASS_ELEMENT_HPP_INCLUDED

#include <fcppt/is_strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Type,
	typename Enable = void
>
struct default_initialize_class_element;


template<
	typename Type
>
struct default_initialize_class_element<
	Type,
	typename boost::enable_if<
		fcppt::is_strong_typedef<
			Type
		>
	>::type
>
{
	static
	Type
	execute()
	{
		return
			Type(
				typename Type::value_type()
			);
	}
};

template<
	typename Type
>
struct default_initialize_class_element<
	Type,
	typename boost::disable_if<
		fcppt::is_strong_typedef<
			Type
		>
	>::type
>
{
	static
	Type
	execute()
	{
		return
			Type();
	}
};

}
}
}

#endif
