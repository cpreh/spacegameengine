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


#ifndef MAJUTSU_MEMORY_DETAIL_INIT_RAW_MEMORY_HPP_INCLUDED
#define MAJUTSU_MEMORY_DETAIL_INIT_RAW_MEMORY_HPP_INCLUDED

#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/mpl/at.hpp>
#include <fcppt/config/external_end.hpp>

namespace majutsu
{
namespace memory
{
namespace detail
{

template<
	typename Memory
>
class init_raw_memory
{
	FCPPT_NONASSIGNABLE(
		init_raw_memory
	);
public:
	explicit init_raw_memory(
		Memory &_memory
	)
	:
		memory_(_memory)
	{}

	template<
		typename Pair
	>
	void
	operator()(
		Pair const &_pair
	) const
	{
		memory_. template set_internal<
			typename boost::mpl::at_c<
				Pair,
				1
			>::type
		>(
			boost::fusion::at_c<
				0
			>(
				_pair
			)
		);
	}
private:
	Memory &memory_;
};

}
}
}

#endif
