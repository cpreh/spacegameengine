/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "../shared_ptr.hpp"
#include "../export.hpp"
#include "types.hpp"
#include <boost/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace font
{

class SGE_CLASS_SYMBOL drawer : boost::noncopyable {
public:
	typedef std::size_t size_type;
	virtual void begin_rendering(
		size_type buffer_chars,
		pos const& start,
		dim size) = 0;
	virtual void draw_char(
		char_type,
		pos const&,
		const_image_view const &data) = 0;
	virtual void end_rendering() = 0;
	SGE_SYMBOL virtual ~drawer();
};

typedef shared_ptr<drawer> drawer_ptr;

}
}

#endif
