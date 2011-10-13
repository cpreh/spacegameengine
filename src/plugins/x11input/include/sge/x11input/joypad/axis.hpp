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


#ifndef SGE_X11INPUT_JOYPAD_AXIS_HPP_INCLUDED
#define SGE_X11INPUT_JOYPAD_AXIS_HPP_INCLUDED

#include <sge/input/info/id.hpp>
#include <fcppt/assert/pre.hpp>

namespace sge
{
namespace x11input
{
namespace joypad
{

template<
	typename Ret,
	typename InfoContainer
>
Ret const
axis(
	input::info::id const _id,
	InfoContainer const &_info
)
{
	typename InfoContainer::id const id(
		_id
	);

	FCPPT_ASSERT_PRE(
		id
		< _info.size()
	)

	return
		Ret(
			_info[
				id
			].code(),
			id
		);
}

}
}
}

#endif
