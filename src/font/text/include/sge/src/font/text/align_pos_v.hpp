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


#ifndef SGE_SRC_FONT_TEXT_ALIGN_POS_V_HPP_INCLUDED
#define SGE_SRC_FONT_TEXT_ALIGN_POS_V_HPP_INCLUDED

#include <sge/font/dim.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/text/align_v.hpp>
#include <sge/font/text/part.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


namespace sge
{
namespace font
{
namespace text
{

inline
void
align_pos_v(
	font::pos &_pos,
	font::dim const &_max_sz,
	text::part const &_total_size,
	text::align_v::type const _align_v
)
{
	switch(
		_align_v
	)
	{
	case align_v::center:
		_pos.y() += (_max_sz.h() - _total_size.size().h()) / 2;
		return;
	case align_v::bottom:
		_pos.y() += _max_sz.h() - _total_size.size().h();
		return;
	case align_v::top:
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

}
}
}

#endif
