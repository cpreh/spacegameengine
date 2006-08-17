#include <limits>
#include <locale>
#include "../renderer.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../renderer_types.hpp"
#include "../transform.hpp"
#include "../lock_ptr.hpp"
#include "../font.hpp"

sge::font::font(const renderer_ptr r, const font_system_ptr font_sys, const std::string& font_name, const font_weight weight)
 : r(r), last_color(colors::transparent),
 impl(font_sys->create_font(r,font_name,weight)),
 font_height_pixel(impl->optimal_font_height())
{}

sge::text_size sge::font::draw_text(const string_type& text, const text_pos pos,
                                    const text_size max_sz, const color col, const text_flag_t flags)
{
	if(text.empty())
		return;
	if(!last_texture)
		last_texture = impl->load_char(text[0]).second;
	last_index = 0;

	const vertex_buffer::size_type vbsize = text.size()*4;
	const index_buffer::size_type ibsize = text.size()*6;

	if(vb->size() < vbsize)
		vb->resize(vbsize);

	if(ib->size() < ibsize)
		ib->resize(ibsize);

	text_pos start_pos = pos;
	if(tflags & TXTF_AlignVCenter || tflags & TXTF_AlignBottom)
	{
		const text_unit text_height = string_size(text.begin(),text.end(),width,tflags).h;
		if(tflags & TXTF_AlignVCenter)
			start_pos.y += (size.h - font_height()) / 2.f;
		else if(tflags & TXTF_AlignBottom)
			start_pos.y += size.h - font_height();
		if(start_pos.y < pos.y)
			start_pos.y = pos.y;
	}

	lock_ptr<vertex_buffer_ptr> _lock(vb,LF_Discard);
	vertex_buffer::iterator vit = vb->begin();

	text_unit w = line_width(sbeg,send,tflags);
	if(tflags & TXTF_NoMultiLine)
	{
		draw_line(vit, start_pos, sbeg, send, tflags);
		return;
	}
	while(sbeg != send)
	{
		draw_line(vit, start_pos, sbeg, send, tflags);
		w = line_width(sbeg,send,tflags);
	}
}

void sge::font::draw_line(vertex_buffer::iterator& it, text_pos pos, const text_size size, const string_type::const_iterator beg, const string_type::const_iterator end, const text_flag_t tflags)
{
	if(tflags & TXTF_AlignHCenter)
		pos.x += (size.w - w) / 2;
	else if(tflags & TXTF_AlignRight)
		pos.x += size.w - w;
	
	for(; sbeg != send; ++sbeg)
	{
		const font_reg   reg = impl->load_char(*sbeg);
		const text_size  sz = char_size(*sbeg);
		const text_unit  top = pos.y + ch_pos.vshift * font_height(),
		                 bottom = top + sz.h;

		fill_sprite_in_vb(vit, text_rect(pos.x,top,pos.x+sz.w,bottom), reg.first);
		if(last_texture != reg.second)
		{
			const size_type cur_index = std::distance(vb->begin(),vit);
			jobs.push_back(job(last_texture, last_index, cur_index-1));
			last_index = cur_index;
		}
		++vit;
		pos.x += sz.w;
	}

}

sge::text_unit sge::font::char_width(const char_type ch) const
{
	const text_rect tp = impl->load_char().first;
	return (tp.right - tp.left); // FIXME
}

sge::text_unit sge::font::text_width_unformatted(string_type::const_iterator sbeg, const string_type::const_iterator send) const
{
	return std::accumulate(sbeg,send,0,boost::bind(char_width,this));
}

sge::text_size sge::font::text_size(string_type::const_iterator sbeg, const string_type::const_iterator send, const text_unit width, const text_flag_t flags) const
{
	if(tflags & TXTF_NoMultiLine)
		return text_size(line_width(sbeg,end,width,flags),font_height());

	text_size sz;
	while(sbeg != send)
	{
		sz.w += line_width(sbeg,send,width,flags);
		sz.h += font_height();
	}
	return sz;
}

sge::text_unit sge::font::line_width(string_type::const_iterator beg, const string_type::const_iterator end, const text_unit width, const text_flag_t tflags)
{
	if(tflags & TXTF_NoMultiLine)
		return text_width_unformatted(beg,end);

	text_unit w(0), last_width(0);
	string_type::const_iterator last_white = sbeg;

	for(;sbeg != send; ++sbeg)
	{
		if(std::isspace(*sbeg,std::locale()))
		{
			last_white = sbeg;
			lastwidth = w;
		}
		w += char_width(*sbeg);
		if(lastsize > 0 && w > width)
			return lastsize;
	}
	return w;
}

void sge::font::flush_text()
{
	set_parameters();
	std::sort(jobs.begin(),jobs.end(),same_texture);
	lock_ptr<index_buffer_ptr> _lock(ib,LF_Discard);

	index_buffer::iterator iib = ib->begin();
	for(job_array::const_iterator it = jobs.begin(); it != jobs.end(); ++it)
		for(size_type i = it->first_index; i <= it->last_index; ++i)
			fill_indices();
	jobs.clear();
}

void sge::font::set_parameters()
{
	r->set_matrix(MU_Projection,matrix_orthogonal_xy<space_unit>());
	r->set_texture(0,impl->get_texture());
	r->set_bool_state(BS_EnableAlphaBlending,true);
	r->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
	r->set_int_state(IS_AmbientLightColor,col);
	r->set_filter_state(0,FARG_MinFilter,FARGV_Point);
	r->set_filter_state(0,FARG_MagFilter,FARGV_Point);
}
