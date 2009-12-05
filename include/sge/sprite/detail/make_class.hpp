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

#include <sge/sprite/primitives/pos.hpp>
#include <sge/sprite/primitives/dim.hpp>
#include <sge/sprite/primitives/float.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/depth.hpp>
#include <majutsu/memory/fusion.hpp>
#include <majutsu/class.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/copy.hpp>

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
		typename boost::mpl::transform<
			typename boost::mpl::copy<
				boost::mpl::vector3<
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
						typename primitives::float_<
							typename Choices::float_type
						>::type,
						roles::depth
					>
				>,
				boost::mpl::front_inserter<
					Elements
				>
			>::type,
			boost::mpl::bind2<
				boost::mpl::_1,
				Choices,
				Elements
			>
		>::type,
		majutsu::memory::fusion
	> type;
};

}
}
}

#endif
