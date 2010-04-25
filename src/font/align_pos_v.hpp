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


#ifndef SGE_FONT_ALIGN_POS_V_HPP_INCLUDED
#define SGE_FONT_ALIGN_POS_V_HPP_INCLUDED

#include <sge/font/pos.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/text_size.hpp>
#include <sge/font/align_v.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

namespace sge
{
namespace font
{

inline
void
align_pos_v(
	pos &pos_,
	dim const &max_sz,
	text_size const &total_size,
	align_v::type const align_v
)
{
	switch(align_v)
	{
	case align_v::center:
		pos_.y() += (max_sz.h() - total_size.size().h()) / 2;
		return;
	case align_v::bottom:
		pos_.y() += max_sz.h() - total_size.size().h();
		return;
	case align_v::top:
		return;
	}

	throw exception(
		FCPPT_TEXT("Invalid font::align_v!")
	);
}

}
}

#endif
