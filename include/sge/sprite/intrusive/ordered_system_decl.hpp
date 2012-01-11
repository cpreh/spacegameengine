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


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_SYSTEM_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_SYSTEM_DECL_HPP_INCLUDED

#include <sge/sprite/intrusive/ordered_system_fwd.hpp>
#include <sge/sprite/intrusive/system_fwd.hpp>
#include <sge/sprite/intrusive/detail/order_map.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{

template<
	typename Choices,
	typename Order
>
class ordered_system
{
	FCPPT_NONCOPYABLE(
		ordered_system
	);
public:
	typedef Order order;

	typedef sge::sprite::intrusive::system<
		Choices
	> system;

	typedef Choices choices;

	typedef typename system::connection_base connection_base;

	ordered_system();

	~ordered_system();

	system &
	get(
		order const &
	);

	connection_base &
	connection(
		order const &
	);

	template<
		typename Function
	>
	void
	for_each(
		Function const &
	);
private:
	typedef typename sge::sprite::intrusive::detail::order_map<
		order,
		system
	>::type order_map;

	order_map systems_;
};

}
}
}

#endif
