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


#ifndef SGE_SPRITE_PROCESS_ALL_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_ALL_HPP_INCLUDED

#include <sge/sprite/process/default_options.hpp>
#include <sge/sprite/process/with_options.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace process
{

template<
	typename Range,
	typename Buffers,
	typename Compare
>
void
all(
	Range const &_range,
	Buffers &_buffers,
	Compare const &_compare
)
{
	sge::sprite::process::with_options<
		typename sge::sprite::process::default_options<
			typename std::iterator_traits<
				typename Range::iterator
			>::value_type::choices,
			Compare
		>::type
	>(
		_range,
		_buffers,
		_compare
	);
}

}
}
}

#endif
