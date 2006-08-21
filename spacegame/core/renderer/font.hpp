#ifndef SGE_FONT_HPP_INCLUDED
#define SGE_FONT_HPP_INCLUDED

#include <cstddef>
#include <string>
#include <vector>
#include "../main/shared_ptr.hpp"
#include "../main/types.hpp"
#include "./renderer_types.hpp"
#include "./index_buffer.hpp"
#include "./vertex_buffer.hpp"
#include "./texture.hpp"
#include "./font_types.hpp"
#include "./renderer.hpp"
#include "../font/font_system.hpp"
#include "../font/font_impl.hpp"

namespace sge
{
class font {
	friend class cached_text;
public:
	typedef font_char char_type;
	typedef font_string string_type;
	typedef std::size_t size_type;
	
	font(renderer_ptr r, font_system_ptr font_sys, const std::string& font_name, font_weight weight = FW_Normal);
	
	void font_height(unsigned scale);
	font_unit font_height() const;
	font_unit optimal_font_height_base() const;
	
	font_size draw_text(const string_type& text, font_pos pos, font_size max_size, color col, font_flag_t flags = FTF_Default);
	
	font_unit text_width_unformatted(string_type::const_iterator sbeg, string_type::const_iterator& send, const font_unit width) const;
	font_unit char_width(char_type ch) const;
	unsigned char_width_pixel(char_type ch) const;
	font_size text_size(string_type::const_iterator beg, string_type::const_iterator end, font_unit width, font_flag_t flags = FTF_Default) const;

	void set_parameters();
private:
	font_unit line_width(string_type::const_iterator beg, string_type::const_iterator& end, font_unit width, font_flag_t tflags) const;
	void draw_line(vertex_buffer::iterator& it, font_pos pos, font_unit width, font_size max_sz, string_type::const_iterator beg, string_type::const_iterator end, font_flag_t tflags);
	void flush_text();

	struct job {
		job(const texture_ptr tex, const size_type first_index, const size_type last_index)
			: tex(tex), first_index(first_index), last_index(last_index) {}
		texture_ptr tex;
		size_type first_index, last_index;
	};
	typedef std::vector<job> job_array;

	renderer_ptr              r;
	font_impl_ptr             impl;
	unsigned                  font_height_pixel;
	vertex_buffer_ptr         vb;
	index_buffer_ptr          ib;
	job_array                 jobs;
	texture_ptr               last_texture;
	size_type                 last_index;
};

typedef shared_ptr<font> font_ptr;

}

#endif
