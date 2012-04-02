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


#ifndef SGE_SPRITE_DEFAULT_INITIALIZE_CLASS_HPP_INCLUDED
#define SGE_SPRITE_DEFAULT_INITIALIZE_CLASS_HPP_INCLUDED

#include <sge/sprite/detail/default_initialize_class_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/container/vector/vector10.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/end.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Class
>
Class const
default_initialize_class()
{
	typedef typename Class::memory_type::types types;

	return
		Class(
			boost::fusion::as_vector(
				sge::sprite::detail::default_initialize_class_impl<
					boost::mpl::empty<
						types
					>::value
				>:: template execute<
					typename boost::mpl::begin<
						types
					>::type,
					typename boost::mpl::end<
						types
					>::type
				>(
					boost::fusion::vector0<>()
				)
			)
		);
}

}
}

#endif
