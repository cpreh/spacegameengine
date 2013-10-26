
/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_PARAMETERS_TO_ELEMENTS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PARAMETERS_TO_ELEMENTS_IMPL_HPP_INCLUDED

#include <sge/sprite/detail/parameters/contains_element.hpp>
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
namespace parameters
{

template<
	typename Dest,
	typename Types,
	typename Source,
	typename... Args
>
inline
typename
boost::enable_if<
	boost::mpl::empty<
		Types
	>,
	Dest
>::type
to_elements_impl(
	Source const &,
	Args &&..._args
)
{
	return
		Dest(
			std::forward<
				Args
			>(
				_args
			)...
		);
}

template<
	typename Dest,
	typename Types,
	typename Source,
	typename... Args
>
inline
typename
boost::disable_if<
	boost::mpl::empty<
		Types
	>,
	Dest
>::type
to_elements_impl(
	Source const &_source,
	Args &&..._args
)
{
	return
		sge::sprite::detail::parameters::to_elements_impl<
			Dest,
			typename
			boost::mpl::pop_front<
				Types
			>::type
		>(
			_source,
			std::forward<
				Args
			>(
				_args
			)...,
			_source. template get<
				typename
				boost::mpl::front<
					Types
				>::type::alias
			>()
		);
}

}
}
}
}

#endif
