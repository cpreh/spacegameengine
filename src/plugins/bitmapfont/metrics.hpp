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


#ifndef SGE_BITMAPFONT_METRICS_HPP_INCLUDED
#define SGE_BITMAPFONT_METRICS_HPP_INCLUDED

#include "char_metric_fwd.hpp"
#include <sge/font/metrics.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/char_type.hpp>
#include <map>

namespace sge
{
namespace bitmapfont
{

class metrics : public font::metrics {
public:
	explicit metrics(
		filesystem::path const &);
	~metrics();

	font::char_metric_ptr const
	load_char(
		char_type);

	font::unit
	line_height() const;
private:
	font::unit line_height_;

	typedef std::map<
		char_type,
		char_metric_ptr
	> char_map;

	char_map char_map_;
};

}
}

#endif
