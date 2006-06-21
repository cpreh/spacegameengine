#ifndef SGE_CACHED_TEXT_HPP_INCLUDED
#define SGE_CACHED_TEXT_HPP_INCLUDED

#include "./font_types.hpp"
#include "./vertex_buffer.hpp"
#include "./index_buffer.hpp"

namespace sge
{
class font;

class cached_text {
public:
	typedef sge::text_pos text_pos;
	cached_text(font& f, const std::string& text, text_pos pos, text_size max_size, color col, text_flag_t flags);
	void draw();
	text_size size() const { return sz; }
	void restore();
	font& get_font() const { return f; }
private:
	void init();
	font&               f;
	std::string         text;
	text_pos            pos;
	color               col;
	text_flag_t         flags;
	text_size           sz;
	text_size           max_size;
	vertex_buffer_ptr   vb;
	index_buffer_ptr    ib;
	unsigned            count;
};

}

#endif
