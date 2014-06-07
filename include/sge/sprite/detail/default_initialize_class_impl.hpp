/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_DEFAULT_INITIALIZE_CLASS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_DEFAULT_INITIALIZE_CLASS_IMPL_HPP_INCLUDED

#include <sge/sprite/detail/default_initialize_class_element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/utility/enable_if.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Class,
	typename Types,
	typename... Args
>
inline
typename
boost::enable_if<
	boost::mpl::empty<
		Types
	>,
	Class
>::type
default_initialize_class_impl(
	Args && ..._args
)
{
	return
		Class(
			std::forward<
				Args
			>(
				_args
			)...
		);
}

template<
	typename Class,
	typename Types,
	typename... Args
>
inline
typename
boost::disable_if<
	boost::mpl::empty<
		Types
	>,
	Class
>::type
default_initialize_class_impl(
	Args && ..._args
)
{
	typedef
	typename
	boost::mpl::front<
		Types
	>::type
	role;

	return
		sge::sprite::detail::default_initialize_class_impl<
			Class,
			typename
			boost::mpl::pop_front<
				Types
			>::type
		>(
			std::forward<
				Args
			>(
				_args
			)...,
			typename
			role::tag{} =
				sge::sprite::detail::default_initialize_class_element<
					typename
					role::wrapped::type
				>::execute()
		);
}

}
}
}

#endif
