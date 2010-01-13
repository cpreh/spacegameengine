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


#ifndef SGE_SPRITE_INTRUSIVE_TAG_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_TAG_HPP_INCLUDED

#include <sge/sprite/primitives/adder.hpp>
#include <sge/sprite/primitives/order.hpp>
#include <sge/sprite/roles/adder.hpp>
#include <sge/sprite/roles/order.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace sprite
{
namespace intrusive
{

struct tag
{
	template<
		typename Choices
	>
	struct apply
	{
		typedef majutsu::composite<
			boost::mpl::vector2<
				majutsu::role<
					primitives::order::type,
					roles::order
				>,
				majutsu::role<
					typename primitives::adder<
						Choices
					>::type,
					roles::adder
				>
			>
		> type;
	};
};

}
}
}

#endif
