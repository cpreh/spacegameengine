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



#ifndef SGE_FREETYPE_METRICS_HPP_INCLUDED
#define SGE_FREETYPE_METRICS_HPP_INCLUDED

#include "library.hpp"
#include "face.hpp"
#include "freetype.hpp"
#include <sge/filesystem/path.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/size_type.hpp>
#include <sge/font/unit.hpp>
#include <sge/char.hpp>
#include <map>

namespace sge
{
namespace ft
{

class metrics : public font::metrics {
public:
	metrics(
		library &lib,
		filesystem::path const &font_path,
		font::size_type font_height);
	
	font::char_metric_ptr const
	load_char(
		char_type c);
	
	font::unit line_height() const;
private:
	face face_;
	font::size_type pixel_size;

	typedef std::map<
		char_type,
		font::char_metric_ptr
	> buffer_type;

	buffer_type buffer;
};

}
}

#endif
