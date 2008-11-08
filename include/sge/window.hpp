/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (s.stienen@slashlife.org)

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


#ifndef SGE_WINDOW_HPP_INCLUDED
#define SGE_WINDOW_HPP_INCLUDED

#include "math/dim.hpp"
#include "math/vector.hpp"
#include "string.hpp"
#include "export.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{

class SGE_CLASS_SYMBOL window : boost::noncopyable {
public:
	typedef int pos_type;
	typedef unsigned size_type;
	typedef math::vector<pos_type,2> window_pos;
	typedef math::dim<size_type,2> window_size;

	virtual void title(string const &title) = 0;
	virtual window_size const size() const = 0;
	virtual window_pos const viewport_offset() const = 0;
	SGE_SYMBOL size_type width() const;
	SGE_SYMBOL size_type height() const;
	virtual void size(window_size const &newsize) = 0;
	SGE_SYMBOL virtual ~window();

	SGE_SYMBOL static void dispatch();
};

//window_ptr create_window();

}

#endif
