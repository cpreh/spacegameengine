/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_CHAR_METRIC_HPP_INCLUDED
#define SGE_CHAR_METRIC_HPP_INCLUDED

#include "../shared_ptr.hpp"
#include "../renderer/font_types.hpp"
#include "../renderer/color.hpp"

namespace sge
{

class char_metric {
public:
	virtual const color* pixmap() const = 0;
	virtual font_unit width() const = 0;
	virtual font_unit height() const = 0;
	virtual font_unit left() const = 0;
	virtual font_unit top() const = 0;
	virtual font_unit x_advance() const = 0;
	virtual ~char_metric() {}
};

typedef shared_ptr<char_metric> char_metric_ptr;

}

#endif
