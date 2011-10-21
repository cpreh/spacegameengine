/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_INTRUSIVE_DETAIL_LEVEL_MAP_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_DETAIL_LEVEL_MAP_HPP_INCLUDED

#include <sge/sprite/intrusive/order.hpp>
#include <sge/sprite/intrusive/detail/list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace detail
{

template<
	typename Choices
>
struct level_map
{
	typedef boost::ptr_map<
		order,
		typename list<
			Choices
		>::type
	> type;
};

}
}
}
}

#endif
