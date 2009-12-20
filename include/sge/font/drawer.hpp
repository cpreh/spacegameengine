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


#ifndef SGE_FONT_DRAWER_HPP_INCLUDED
#define SGE_FONT_DRAWER_HPP_INCLUDED

#include <sge/font/drawer_fwd.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/image_view.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace font
{

class SGE_CLASS_SYMBOL drawer
{
	FCPPT_NONCOPYABLE(drawer)
public:
	typedef std::size_t size_type;

	virtual void
	begin_rendering(
		size_type buffer_chars,
		pos const &start,
		dim size
	) = 0;

	virtual void
	draw_char(
		fcppt::char_type,
		pos const &,
		const_image_view const &data
	) = 0;

	virtual void
	end_rendering() = 0;

	SGE_SYMBOL virtual ~drawer();
protected:
	SGE_SYMBOL drawer();
};

}
}

#endif
