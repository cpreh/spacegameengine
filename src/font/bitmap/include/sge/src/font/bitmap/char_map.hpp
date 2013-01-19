/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_FONT_BITMAP_CHAR_MAP_HPP_INCLUDED
#define SGE_SRC_FONT_BITMAP_CHAR_MAP_HPP_INCLUDED

#include <sge/font/char_type.hpp>
#include <sge/src/font/bitmap/char_metric_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{

typedef boost::ptr_map<
	sge::font::char_type,
	sge::font::bitmap::char_metric
> char_map;

}
}
}

#endif
