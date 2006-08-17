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
	text_unit font_height() const;
	text_unit optimal_font_height_base() const;
	
	text_size draw_text(const string_type& text, text_pos pos, text_size max_size, color col, text_flag_t flags = TXTF_AlignLeft | TXTF_AlignTop);
	
	text_unit char_width(char_type ch) const;
	text_unit char_size(char_type ch) const;
	text_size string_size(string_type::const_iterator beg, string_type::const_iterator end) const;
	text_size string_size(string_type::const_iterator beg, string_type::const_iterator end, text_unit width, text_flag_t flags = TXTF_AlignLeft | TXTF_AlignTop) const;
private:
	unsigned create_text_res(vertex_buffer_ptr& vb, index_buffer_ptr& ib, text_pos pos, text_size& size,
	                         const string_type& text, text_flag_t tflags, bool static_buf);
	void draw_ex(vertex_buffer_ptr vb, index_buffer_ptr ib,
	             color col, unsigned count = 0);

	struct job {
		job(const texture_ptr tex, const size_type first, const size_type last)
			: tex(tex), first(first), last(last) {}
		texture_ptr tex;
		size_type first, last;
	};
	typedef std::vector<job> job_array;

	renderer_ptr              r;
	vertex_buffer_ptr         vb;
	index_buffer_ptr          ib;
	color                     last_color;
	font_impl_ptr             font_sys;
	unsigned                  font_height_pixel;
	job_array                 jobs;
	texture_ptr               last_texture;
	size_type                 last_index;
};

typedef shared_ptr<font> font_ptr;

}

#endif
