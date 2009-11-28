/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED

#include <majutsu/memory/fusion.hpp>
#include <majutsu/class.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/transform_view.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename Elements
>
struct make_class
{
	typedef majutsu::class_<
		typename boost::mpl::transform_view<
			typename boost::mpl::copy<
				boost::mpl::front_inserter<
					Elements
				>,
				boost::mpl::vector<
					majutsu::role<
						typename primitives::pos<
							typename Choices::unit_type
						>::type,
						roles::pos
					>,
					majutsu::role<
						typename primitives::dim<
							typename Choices::unit_type
						>::type,
						roles::size
					>,
					majutsu::role<
						
				>
			>::type,
			boost::mpl::apply<
				boost::mpl::_1,
				Choices
			>
		>::type,
		majutsu::memory::fusion
	> element_type;
};

}
}
}

#endif
