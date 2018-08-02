/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_UNLINK_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_UNLINK_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/detail/destroy.hpp>
#include <sge/sprite/detail/config/is_intrusive.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
void
unlink(
	sge::sprite::object<
		Choices
	> &_this
)
{
	static_assert(
		sge::sprite::detail::config::is_intrusive<
			Choices
		>::value,
		"Sprite must be intrusive"
	);

	sge::sprite::detail::destroy(
		_this
	);

	_this.unlink();
}

}
}
}

#endif
