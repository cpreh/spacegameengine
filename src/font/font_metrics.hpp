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


#ifndef SGE_FONT_METRICS_HPP_INCLUDED
#define SGE_FONT_METRICS_HPP_INCLUDED

#include "../shared_ptr.hpp"
#include "../renderer/font_types.hpp"
#include "../renderer/texture.hpp"

namespace sge
{

struct font_entity {
	font_rect rect;
	texture_ptr tex;
	font_unit left;
	font_unit top;
	font_unit x_advance;
	font_unit v_scale;
	font_unit h_scale;
};

class font_metrics {
public:
	virtual ~font_metrics(){}
	virtual const font_entity& load_char(font_char c) = 0;
	virtual unsigned optimal_height_base() const = 0;
};

typedef shared_ptr<font_metrics> font_metrics_ptr;

}

#endif
