#include "../cached_text.hpp"
#include "../font.hpp"


sge::cached_text::cached_text(font& f, const std::string& text, const text_pos pos, const text_size max_size, const color col, const text_flag_t flags)
: f(f), text(text), pos(pos), col(col), flags(flags), sz(max_size), max_size(max_size)
{
	init();
}

void sge::cached_text::init()
{
	count = f.create_text_res(vb,ib,pos,sz,text,flags,true);
}

void sge::cached_text::draw()
{
	f.draw_ex(vb,ib,col,count);
}

void sge::cached_text::restore()
{
	init();
}
