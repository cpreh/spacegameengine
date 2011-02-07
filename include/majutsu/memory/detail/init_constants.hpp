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


#ifndef MAJUTSU_MEMORY_DETAIL_INIT_CONSTANTS_HPP_INCLUDED
#define MAJUTSU_MEMORY_DETAIL_INIT_CONSTANTS_HPP_INCLUDED

#include <majutsu/is_constant.hpp>
#include <fcppt/nonassignable.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/utility/enable_if.hpp>

namespace majutsu
{
namespace memory
{
namespace detail
{

template<
	typename Memory
>
class init_constants
{
	FCPPT_NONASSIGNABLE(
		init_constants
	);
public:
	explicit init_constants(
		Memory &_mem
	)
	:
		mem_(_mem)
	{}

	template<
		typename Iterator
	>
	typename boost::enable_if<
		majutsu::is_constant<
			typename boost::mpl::deref<
				Iterator
			>::type
		>,
		void
	>::type
	operator()(
		Iterator &
	) const
	{
		typedef typename boost::mpl::deref<
			Iterator
		>::type type;

		mem_. template set_internal<
			Iterator
		>(
			type::value
		);
	}

	template<
		typename Iterator
	>
	typename boost::disable_if<
		majutsu::is_constant<
			typename boost::mpl::deref<
				Iterator
			>::type
		>,
		void
	>::type
	operator()(
		Iterator &
	) const
	{}
private:
	Memory &mem_;
};

}
}
}

#endif
