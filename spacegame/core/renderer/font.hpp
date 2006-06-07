#ifndef SGE_FONT_HPP_INCLUDED
#define SGE_FONT_HPP_INCLUDED

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
		
		SGECOREDLLAPI font(renderer_ptr r, font_system_ptr font_sys, const std::string& font_name, bool italic = false, font_weight weight = FW_Normal, text_unit height = 0.1f, const std::locale& loc = std::locale());
		void font_height(text_unit sz) { _font_height = sz; }
		text_unit font_height() const { return _font_height; }
		SGECOREDLLAPI text_size draw_text(const string_type& text, text_pos pos, text_size max_size, color col, text_flag_t flags = TXTF_AlignLeft | TXTF_AlignTop);
		SGECOREDLLAPI text_size char_size(char_type ch) const;
		SGECOREDLLAPI text_size string_size(string_type::const_iterator beg, string_type::const_iterator end) const;
		SGECOREDLLAPI text_size string_size(const string_type& s, string_type::size_type pos = 0, string_type::size_type count = string_type::npos) const;
		SGECOREDLLAPI text_size string_size(const string_type& text, text_unit width, text_flag_t flags = TXTF_AlignLeft | TXTF_AlignTop) const;
		SGECOREDLLAPI text_size string_size(string_type::const_iterator beg, string_type::const_iterator end, text_unit width, text_flag_t flags = TXTF_AlignLeft | TXTF_AlignTop) const;
		SGECOREDLLAPI bool is_print(char c) const;
	private:
		unsigned create_text_res(vertex_buffer_ptr& vb, index_buffer_ptr& ib, text_pos pos, text_size& size,
		                         const string_type& text, text_flag_t tflags, bool static_buf);
		void draw_ex(vertex_buffer_ptr vb, index_buffer_ptr ib,
		             const color col, unsigned count = 0);

		renderer_ptr              r;
		std::locale               loc;
		vertex_buffer_ptr         vb;
		index_buffer_ptr          ib;
		unsigned                  screen_width;
		unsigned                  screen_height;
		unsigned                  tab_width;
		vertex_buffer::size_type  vertex_count;
		color                     last_color;
		text_unit                 _font_height;
		font_information          font_info;
		font_system_ptr           font_sys;
	};
	typedef shared_ptr<font> font_ptr;
}

#endif
