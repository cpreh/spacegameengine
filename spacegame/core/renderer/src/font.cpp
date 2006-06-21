#include <limits>
#include <locale>
#include "../renderer.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../renderer_types.hpp"
#include "../transform.hpp"
#include "../lock_ptr.hpp"
#include "../font.hpp"

namespace {
	std::size_t char_to_index(const char ch) { return ch - std::numeric_limits<char>::min(); }
}

sge::font::font(const renderer_ptr r, const font_system_ptr font_sys, const std::string& font_name, const bool italic, const font_weight weight, const text_unit height, const std::locale& loc)
 : r(r), loc(loc), screen_width(r->get_screen_width()),
 screen_height(r->get_screen_height()), tab_width(4),
 vertex_count(0), last_color(colors::transparent), _font_height(height),
 font_info(font_sys->create_font(r,font_name,italic,weight,height,loc)), font_sys(font_sys)
{}

sge::text_size sge::font::draw_text(const string_type& text, const text_pos pos,
                                    text_size sz, const color col, const text_flag_t flags)
{
	const unsigned count = create_text_res(vb,ib,pos,sz,text,flags,false);
	draw_ex(vb,ib,col,count);
	return sz;
}

sge::text_size sge::font::char_size(const char_type ch) const
{
	const font_information::rect& tp = font_info.positions.at(char_to_index(ch)).texture_pos;
	const text_unit scale = font_height() / font_info.font_height;
	return text_size((tp.right - tp.left) * scale, (tp.bottom - tp.top) * scale);
}

sge::text_size sge::font::string_size(const string_type& s,
                                      const string_type::size_type pos,
                                      const string_type::size_type count) const
{
	return string_size(s.begin()+pos,s.begin()+pos+count);
}

sge::text_size sge::font::string_size(string_type::const_iterator sbeg,
                                      const string_type::const_iterator send) const
{
	text_size sz;
	for(; sbeg != send; ++sbeg)
	{
		const text_size ch_size = char_size(*sbeg);
		sz.w += ch_size.w;
		sz.h = std::max(sz.h,ch_size.h);
	}
	return sz;
}

sge::text_size sge::font::string_size(const string_type& text,
                                      const text_unit width,
                                      const text_flag_t flags) const
{
	return string_size(text.begin(),text.end(),width,flags);
}

sge::text_size sge::font::string_size(string_type::const_iterator sbeg,
                                      const string_type::const_iterator send,
                                      const text_unit width,
                                      const text_flag_t flags) const
{
	const text_unit lineh = font_height();
	text_size sz;
	while(sbeg != send)
	{
		sz.h += lineh;
		std::string::const_iterator lastwhite = sbeg;
		text_unit lastsize = 0;
		text_unit w = 0;
		for(; sbeg != send  && *sbeg != '\n' && w < width; ++sbeg)
		{
			if(std::isspace(*sbeg,loc))
			{
				lastwhite = sbeg;
				lastsize = w;
			}
			w += char_size(*sbeg).w;
		}
		if(flags & TXTF_NoMultiLine)
			return text_size(w,lineh);
		// Whitespaces?
		if(lastsize > 0 && w > width)
		{
			w = lastsize;
			sbeg = ++lastwhite;
		}
		sz.w = std::max(w,sz.w);
	}
	return sz;
}

bool sge::font::is_print(const char ch) const
{
	const font_information::rect& r = font_info.positions.at(char_to_index(ch)).texture_pos;
	return r.left != r.right;
}

unsigned sge::font::create_text_res(vertex_buffer_ptr& vb,
                                    index_buffer_ptr& ib, const text_pos pos, text_size& size,
				    const string_type& text, const text_flag_t tflags, const bool static_buf)
{
	const unsigned chr_count = unsigned(text.size());
	if(chr_count == 0)
		return 0;

	unsigned count = 0;
	const text_unit width = size.w, height = size.h;
	const resource_flag_t flags = resource_flag_t(static_buf ? RF_WriteOnly : resource_flag_t(RF_WriteOnly) | RF_Dynamic);
	const vertex_buffer::size_type vbsize = chr_count*4;
	const index_buffer::size_type ibsize = chr_count*6;
	if(!vb || vb->flags() != flags)
		vb = r->create_vertex_buffer(vertex_format().add(VU_Pos).add(VU_Tex),vbsize,flags);
	vb->resize(vbsize);

	if(!ib || ib->flags() != flags || ib->size() < ibsize)
	{
		ib = r->create_index_buffer(ibsize,flags);
		lock_ptr<index_buffer> l(ib.get(),LF_Discard);
		index_buffer::iterator ibit = ib->begin();
		for(index_buffer::value_type i = 0; i < chr_count; ++i)
		{
			const index_buffer::value_type delta = i*4;
			(*ibit++) = 0 + delta;
			(*ibit++) = 1 + delta;
			(*ibit++) = 2 + delta;
			(*ibit++) = 2 + delta;
			(*ibit++) = 3 + delta;
			(*ibit++) = 0 + delta;
		}
	}

	text_pos start_pos = pos;
	if(tflags & TXTF_AlignVCenter || tflags & TXTF_AlignBottom)
	{
		const text_unit text_height = string_size(text.begin(),text.end(),width,tflags).h;
		if(tflags & TXTF_AlignVCenter)
			start_pos.y += (height - text_height) / 2.f;
		else if(tflags & TXTF_AlignBottom)
			start_pos.y += height - text_height;
		if(start_pos.y < pos.y)
			start_pos.y = pos.y;
	}
	{
		lock_ptr<vertex_buffer> l(vb.get(),LF_Discard);
		vertex_buffer::iterator vit = vb->begin();
		for(string_type::const_iterator beg = text.begin();
		    beg != text.end() && start_pos.y + font_height() < pos.y + height;)
		{
			string_type::const_iterator it = beg,
			                            last_white = beg;
			text_unit last_size = 0;

			text_unit w = 0;
			if(tflags & TXTF_NoMultiLine)
				for(; it != text.end(); ++it)
				{
					const text_unit delta = char_size(*it).w;
					if(delta + w > width)
						break;
					w += delta;
				}
			else
				for(; it != text.end() && (*it) != '\n'; ++it)
				{
					if(std::isspace(*it,loc))
					{
						last_size = w;
						last_white = it;
					}
					w += char_size(*it).w;
					if(w > width && last_size > 0)
					{
						w = last_size;
						it = last_white+1;
						break;
					}
				}

			size.w = std::max(size.w,w);
			// Fill one line
			text_pos pos = start_pos;
			if(tflags & TXTF_AlignHCenter)
				pos.x += (width - w) / 2;
			else if(tflags & TXTF_AlignRight)
				pos.x += width - w;
			
			const string_type::const_iterator send = it;
			for(string_type::const_iterator sbeg = beg; sbeg != send; ++sbeg)
			{
				const font_information::position& ch_pos = font_info.positions.at(char_to_index(*sbeg));
				const font_information::rect&     tp     = ch_pos.texture_pos;
				const text_size bounds = char_size(*sbeg);
				const text_unit top = pos.y + ch_pos.vshift * font_height(),
				                bottom = top + bounds.h;

			/*	(*vit).pos() = text_to_space(pos.x,top);
				(*vit++).tex()[0] = tex_pos(tp.left,tp.top);
				(*vit).pos() = text_to_space(pos.x+bounds.w,top);
				(*vit++).tex()[0] = tex_pos(tp.right,tp.top);
				(*vit).pos() = text_to_space(pos.x+bounds.w,bottom);
				(*vit++).tex()[0] = tex_pos(tp.right,tp.bottom);
				(*vit).pos() = text_to_space(pos.x,bottom);
				(*vit++).tex()[0] = tex_pos(tp.left,tp.bottom);
			*/	
				pos.x += bounds.w;
			}

			count += static_cast<int>(it-beg)*2;
			if(tflags & TXTF_NoMultiLine)
				break;
			start_pos.y += font_height();
			beg = it;
		}
	}
	
	size.h = start_pos.y - pos.y;
	return count;
}

void sge::font::draw_ex(const vertex_buffer_ptr vb, const index_buffer_ptr ib,
                        const color col, unsigned count)
{
	if(count == 0)
		return;
	
	r->set_matrix(MU_Projection,matrix_ortogonal_xy<space_unit>());
	r->set_texture(0,font_info.tex);
	r->set_bool_state(BS_EnableAlphaBlending,true);
	r->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
	r->set_int_state(IS_AmbientLightColor,col);
	r->set_texture_stage_op( 0, SOP_Color,   SOPV_SelectArg1 );
	r->set_texture_stage_arg(0, SARG_Color1, SARGV_Diffuse   );
	r->set_texture_stage_op( 0, SOP_Alpha,   SOPV_SelectArg1 );
	r->set_texture_stage_arg(0, SARG_Alpha1, SARGV_Texture   );
	r->set_texture_stage_op( 1, SOP_Color,   SOPV_Disable    );
	r->set_texture_stage_op( 1, SOP_Alpha,   SOPV_Disable    );
	r->render(vb,ib,0,vb->size(),PT_Triangle,count);
}
