/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_BITMAPFONT_CHAR_METRIC_HPP_INCLUDED
#define SGE_BITMAPFONT_CHAR_METRIC_HPP_INCLUDED

#include <sge/font/char_metric.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/variant/object_decl.hpp>

namespace sge
{
namespace bitmapfont
{

class char_metric : public font::char_metric {
public:
	char_metric(
		font::const_image_view const &,
		font::pos const &offset,
		font::unit x_advance);

	~char_metric();

	font::const_image_view const
	pixmap() const;

	font::pos const
	offset() const;

	font::unit
	x_advance() const;
private:
	font::const_image_view const pixmap_;
	font::pos const offset_;
	font::unit const x_advance_;
};

}
}

#endif
