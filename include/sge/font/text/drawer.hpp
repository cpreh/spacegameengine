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


#ifndef SGE_FONT_TEXT_DRAWER_HPP_INCLUDED
#define SGE_FONT_TEXT_DRAWER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/font/const_image_view.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/text/char_type.hpp>
#include <sge/font/text/drawer_fwd.hpp>
#include <sge/font/text/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{
namespace text
{

class SGE_CLASS_SYMBOL drawer
{
	FCPPT_NONCOPYABLE(
		drawer
	);
public:
	typedef std::size_t size_type;

	virtual void
	begin_rendering(
		size_type buffer_chars,
		pos const &start,
		dim const &size
	) = 0;

	virtual void
	draw_char(
		font::text::char_type,
		pos const &,
		const_image_view const &data
	) = 0;

	virtual void
	end_rendering() = 0;

	SGE_FONT_TEXT_SYMBOL
	virtual ~drawer() = 0;
protected:
	SGE_FONT_TEXT_SYMBOL
	drawer();
};

}
}
}

#endif
