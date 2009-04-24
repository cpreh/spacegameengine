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



#ifndef SGE_FONT_OBJECT_HPP_INCLUDED
#define SGE_FONT_OBJECT_HPP_INCLUDED

#include <sge/font/pos.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/drawer_fwd.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/align_v.hpp>
#include <sge/font/flags.hpp>
#include <sge/string.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace font
{

class text_size;

class SGE_CLASS_SYMBOL object {
public:
	SGE_SYMBOL explicit object(
		metrics_ptr metrics,
		drawer_ptr drawer = drawer_ptr());
	SGE_SYMBOL ~object();

	SGE_SYMBOL unit height() const;

	SGE_SYMBOL font::text_size const
	draw_text(
		string const &text,
		pos const &start_pos,
		dim const &max_size,
		align_h::type = align_h::left,
		align_v::type = align_v::top,
		flag_t flags = flags::default_) const;

	SGE_SYMBOL font::text_size const
	line_width(
		string::const_iterator beg,
		string::const_iterator end,
		unit width,
		flag_t tflags) const;

	SGE_SYMBOL font::text_size const
	text_size(
		string::const_iterator beg,
		string::const_iterator end,
		dim const &max_size,
		flag_t flags = flags::default_) const;

	SGE_SYMBOL font::text_size const
	text_size(
		string const &s, 
		dim const &max_size,
		flag_t flags = flags::default_) const;

	SGE_SYMBOL unit char_space(char_type ch) const;

	SGE_SYMBOL metrics_ptr const metrics() const;
	SGE_SYMBOL drawer_ptr const drawer() const;
private:
	metrics_ptr       metrics_;
	drawer_ptr        drawer_;
};

}
}

#endif
