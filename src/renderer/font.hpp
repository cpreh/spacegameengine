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


#ifndef SGE_FONT_HPP_INCLUDED
#define SGE_FONT_HPP_INCLUDED

#include <cstddef>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include "../shared_ptr.hpp"
#include "../types.hpp"
//#include "types.hpp"
//#include "index_buffer.hpp"
//#include "vertex_buffer.hpp"
//#include "texture.hpp"
#include "font_types.hpp"
#include "font_drawer.hpp"
//#include "renderer.hpp"
#include "../font/font_system.hpp"
#include "../font/font_metrics.hpp"
//#include "../math/matrix.hpp"

namespace sge
{

namespace font_flags
{
	enum type {
		align_left     = 1,
		align_right    = 1 << 1,
		align_hcenter  = 1 << 2,
		align_top      = 1 << 3,
		align_vcenter  = 1 << 4,
		align_bottom   = 1 << 5,
		no_multi_line  = 1 << 6,
		no_line_wrap   = 1 << 7,
		default_       = align_left | align_top
	};
}
typedef unsigned font_flag_t; // FIXME

class font : boost::noncopyable {
public:
	typedef font_char char_type;
	typedef string string_type;
	typedef index_buffer::size_type size_type;

	font(font_metrics_ptr metrics, font_drawer_ptr drawer);

	font_unit height() const;

	font_size draw_text(const string_type& text, font_pos pos, font_size max_size, color col, font_flag_t flags = font_flags::default_);

	struct line_size_t {
		font_unit width;
		string_type::const_iterator end,
		                            next_begin;

		line_size_t(font_unit width, string_type::const_iterator end, string_type::const_iterator next_begin);
		line_size_t(font_unit width, string_type::const_iterator end);
	};

	line_size_t text_width_unformatted(string_type::const_iterator sbeg, string_type::const_iterator send, const font_unit width) const;
	line_size_t line_width(string_type::const_iterator beg, string_type::const_iterator end, font_unit width, font_flag_t tflags) const;
	//font_unit char_width(char_type ch) const;
	font_unit char_space(char_type ch) const;
	font_size text_size(string_type::const_iterator beg, string_type::const_iterator end, font_unit width, font_flag_t flags = font_flags::default_) const;
	font_size text_size(const string_type& s, font_unit width, font_flag_t flags = font_flags::default_) const;
	font_metrics_ptr metrics() const;
	font_drawer_ptr drawer() const;
private:
/*	void set_parameters();
	void add_job(size_type cur_index);
	void flush();

	struct job {
		job(const texture_ptr tex, const size_type first_index, const size_type end_index)
		 : tex(tex), first_index(first_index), end_index(end_index) {}
		texture_ptr tex;
		size_type first_index, end_index;
	};
	typedef std::vector<job> job_array;*/

//	renderer_ptr           rend;
	font_metrics_ptr       metrics_;
	font_drawer_ptr        drawer_;
//	font_unit              _height;
//	vertex_buffer_ptr      vb;
//	index_buffer_ptr       ib;
//	job_array              jobs;
//	texture_ptr            last_texture;
//	size_type              last_index;
};

typedef shared_ptr<font> font_ptr;

}

#endif
