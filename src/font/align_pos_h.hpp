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


#ifndef SGE_FONT_ALIGN_POS_H_HPP_INCLUDED
#define SGE_FONT_ALIGN_POS_H_HPP_INCLUDED

#include <sge/font/pos.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/text_size.hpp>
#include <sge/font/align_h.hpp>
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
align_pos_h(
	pos &pos_,
	dim const &max_sz,
	text_size const &line_size,
	align_h::type const align_h
)
{
	switch(align_h)
	{
	case align_h::center:
		pos_.x() += (max_sz.w() - line_size.size().w()) / 2;
		return;
	case align_h::right:
		pos_.x() += max_sz.w() - line_size.size().w();
		return;
	case align_h::left:
		return;
	}

	throw exception(
		FCPPT_TEXT("Invalid font::align_h!")
	);
}

}
}

#endif
