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


#ifndef SGE_FT_CHAR_METRIC_HPP_INCLUDED
#define SGE_FT_CHAR_METRIC_HPP_INCLUDED

#include <sge/raw_vector.hpp>
#include <sge/string.hpp>
#include <sge/font/types.hpp>
#include <sge/font/char_metric.hpp>

namespace sge
{
namespace ft
{

class face;

class char_metric : public font::char_metric {
public:
	char_metric(
		face &,
		char_type);

	font::const_image_view const pixmap() const;
	font::pos const offset() const;
	font::unit x_advance() const;
private:
	font::image buffer;
	font::pos   offset_;
	font::unit  x_advance_;
};

}
}

#endif
