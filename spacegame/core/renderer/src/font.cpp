#include <limits>
#include <locale>
#include "../renderer.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../renderer_types.hpp"
#include "../transform.hpp"
#include "../lock_ptr.hpp"
#include "../font.hpp"
#include "../../sprite/helper.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

sge::font::font(const renderer_ptr r, const font_system_ptr font_sys, const std::string& font_name, const font_weight weight)
 : r(r),
 impl(font_sys->create_font(r,font_name,weight)),
 font_height_pixel(impl->optimal_height_base())
{}

void sge::font::font_height(unsigned scale)
{
	font_height_pixel = impl->optimal_height_base()*scale;
}

sge::font_unit sge::font::font_height() const
{
	return font_unit(font_height_pixel) / r->screen_height();
}

sge::font_unit sge::font::optimal_font_height_base() const
{
	return font_unit(impl->optimal_height_base()) / r->screen_height();
}

sge::font_size sge::font::draw_text(const string_type& text, const font_pos pos,
                                    const font_size max_sz, const color col, const font_flag_t flags)
{
	if(font_height() > max_sz.h)
		return font_size();
	if(text.empty())
		return font_size();
	if(!last_texture)
		last_texture = impl->load_char(text[0]).tex;
	last_index = 0;

	const vertex_buffer::size_type vbsize = text.size()*4;
	const index_buffer::size_type ibsize = text.size()*6;

	if(vb->size() < vbsize)
		vb->resize(vbsize);

	if(ib->size() < ibsize)
		ib->resize(ibsize);

	font_pos start_pos = pos;
	if(flags & FTF_AlignVCenter || flags & FTF_AlignBottom)
	{
		const font_unit text_height = text_size(text.begin(), text.end(), max_sz.w, flags).h;
		if(flags & FTF_AlignVCenter)
			start_pos.y += (max_sz.h - text_height) / 2.f;
		else if(flags & FTF_AlignBottom)
			start_pos.y += max_sz.h - text_height;
		if(start_pos.y < pos.y)
			start_pos.y = pos.y;
	}

	lock_ptr<vertex_buffer_ptr> _lock(vb,LF_Discard);
	vertex_buffer::iterator vit = vb->begin();

	string_type::const_iterator sbeg = text.begin(), send = text.end();

	r->set_int_state(IS_AmbientLightColor,col);

	if(flags & FTF_NoMultiLine)
	{
		const font_size sz(line_width(sbeg, send, max_sz.w, flags), font_height());
		draw_line(vit, start_pos, sz.w, max_sz, sbeg, send, flags);
		return sz;
	}

	font_size sz;
	while(sbeg != text.end())
	{
		const font_unit w = line_width(sbeg, send, max_sz.w, flags);
		sz.w = std::max(sz.w, w);
		sz.h += font_height();
		draw_line(vit, start_pos, w, max_sz.w, sbeg, send, flags);
	}
	return sz;
}

void sge::font::draw_line(vertex_buffer::iterator& vit, font_pos pos, const font_unit width, const font_size max_sz, string_type::const_iterator sbeg, string_type::const_iterator send, const font_flag_t flags)
{
	if(flags & FTF_AlignHCenter)
		pos.x += (max_sz.w - width) / 2;
	else if(flags & FTF_AlignRight)
		pos.x += max_sz.w - width;

	size_type last_index = 0;
	while(sbeg != send)
	{
		const font_char_rect reg = impl->load_char(*sbeg);
		const font_size      sz(char_width(*sbeg),font_height());
		const font_unit      top = pos.y + reg.top * font_height(),
		                     bottom = pos.y + sz.h;

		++sbeg;

		fill_sprite_in_vb(vit, font_rect(pos.x,top,pos.x+sz.w,bottom), reg.rect);

		if(last_texture != reg.tex || sbeg==send)
		{
			const size_type cur_index = std::distance(vb->begin(), vit);
			jobs.push_back(job(last_texture, last_index, cur_index-1));
			last_index = cur_index;
		}
		pos.x += sz.w;
	}
}

unsigned sge::font::char_width_pixel(const char_type ch) const
{
	const font_char_rect fc = impl->load_char(ch);
	return static_cast<unsigned>((fc.rect.right - fc.rect.left) * fc.tex->width());
}

sge::font_unit sge::font::char_width(const char_type ch) const
{
	return font_unit(char_width_pixel(ch)) / r->screen_width();
}

sge::font_unit sge::font::text_width_unformatted(string_type::const_iterator sbeg, string_type::const_iterator& send, const font_unit width) const
{
	font_unit w(0);
	for(; sbeg != send; ++sbeg)
	{
		if(w + char_width(*sbeg) > width)
			break;
		w += char_width(*sbeg);
	}
	send = sbeg;
	return w;
}

sge::font_size sge::font::text_size(string_type::const_iterator sbeg, string_type::const_iterator send, const font_unit width, const font_flag_t flags) const
{
	if(flags & FTF_NoMultiLine)
		return font_size(line_width(sbeg, send, width, flags), font_height());

	font_size sz;
	while(sbeg != send)
	{
		sz.w += std::max(sz.w, line_width(sbeg, send, width, flags));
		sz.h += font_height();
	}
	return sz;
}

sge::font_unit sge::font::line_width(string_type::const_iterator sbeg, string_type::const_iterator& send, const font_unit width, const font_flag_t flags) const
{
	if(flags & FTF_NoMultiLine)
		return text_width_unformatted(sbeg, send, width);

	font_unit w(0), last_width(0);
	string_type::const_iterator last_white = sbeg;

	for(;sbeg != send; ++sbeg)
	{
		if(std::isspace(*sbeg,std::locale()))
		{
			last_white = sbeg;
			last_width = w;
		}
		w += char_width(*sbeg);
		if(last_width > 0 && w > width)
		{
			send = ++sbeg;
			return last_width;
		}
	}
	return w;
}

void sge::font::flush_text()
{
	set_parameters();
	std::sort(jobs.begin(),jobs.end(), boost::lambda::bind(&job::tex, boost::lambda::_1) < boost::lambda::bind(&job::tex, boost::lambda::_2));
	lock_ptr<index_buffer_ptr> _lock(ib,LF_Discard);

	index_buffer::iterator iib = ib->begin();
	for(job_array::const_iterator it = jobs.begin(); it != jobs.end(); ++it)
	{
		for(size_type i = it->first_index; i <= it->last_index; ++i)
			fill_sprite_indices(iib, i*6);
		if(it->tex != last_texture)
		{
			r->set_texture(0,it->tex);
			last_texture = it->tex;
		}
		r->render(vb, ib, 0, vb->size(), PT_Triangle, (it->last_index-it->first_index+1)*2, it->first_index);	
	}
	jobs.clear();
}

void sge::font::set_parameters()
{
	r->projection_orthogonal();
	r->set_bool_state(BS_EnableAlphaBlending,true);
	r->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
	r->set_filter_state(0,FARG_MinFilter,FARGV_Point);
	r->set_filter_state(0,FARG_MagFilter,FARGV_Point);
}
