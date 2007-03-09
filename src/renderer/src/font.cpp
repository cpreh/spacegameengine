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


#include <vector>
#include "../../types.hpp"
#include "../renderer.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../types.hpp"
#include "../transform.hpp"
#include "../lock_ptr.hpp"
#include "../font.hpp"
#include "../../ucs4.hpp"
#include "../../sprite/helper.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/next_prior.hpp>

sge::font::font(const renderer_ptr rend, const font_system_ptr font_sys, const std::string& font_name, const unsigned quality_in_pixel, const font_weight weight)
 : transformable(rend, matrix_2d_to_3d(), math::matrix_orthogonal_xy()),
   rend(rend),
   impl(font_sys->create_font(rend, font_name, quality_in_pixel ,weight)),
   vb(rend->create_vertex_buffer(vertex_format().add(VU_Pos).add(VU_Tex), 200)),
   ib(rend->create_index_buffer(vb->size()*3/2))
{
	height_pixel_scale(1);
}

void sge::font::height_pixel_scale(const unsigned scale)
{
	height(font_unit(impl->optimal_height_base()*scale) / rend->screen_size().h());
}

sge::font_unit sge::font::height() const
{
	return _height;
}

sge::font_unit sge::font::optimal_height_base() const
{
	return font_unit(impl->optimal_height_base()) / rend->screen_size().h();
}

void sge::font::height(const space_unit h)
{
	_height = h;
}

sge::font_size sge::font::draw_text(const string_type& text, const font_pos start_pos, const font_size max_sz, const color col, const font_flag_t flags)
{
	if(text.empty() || height() > max_sz.h())
		return font_size(0,0);
	last_index = 0;
	last_texture = impl->load_char(text[0]).tex;

	const vertex_buffer::size_type vbsize = text.size()*4;
	const index_buffer::size_type ibsize = text.size()*6;

	if(vb->size() < vbsize)
		vb->resize(vbsize);

	if(ib->size() < ibsize)
		ib->resize(ibsize);

	font_pos pos = start_pos;
	if(flags & FTF_AlignVCenter || flags & FTF_AlignBottom)
	{
		const font_unit text_height = text_size(text.begin(), text.end(), max_sz.w(), flags).h();
		if(flags & FTF_AlignVCenter)
			pos.y() += (max_sz.h() - text_height) / 2.f;
		else if(flags & FTF_AlignBottom)
			pos.y() += max_sz.h() - text_height;
		if(pos.y() < start_pos.y())
			pos.y() = start_pos.y();
	}

	rend->set_int_state(IS_AmbientLightColor,col);

	font_size sz(0,0);
	string_type::const_iterator sbeg(text.begin());

	lock_ptr<vertex_buffer_ptr> _lock(vb,LF_Discard);
	vertex_buffer::iterator vit = vb->begin();

	std::size_t chars_to_draw = 0;
	while(sbeg != text.end() && sz.h() + height() <= max_sz.h())
	{
		const line_size_t line_size = line_width(sbeg, text.end(), max_sz.w(), flags);
		if(line_size.width == 0)
			break;

		pos.x() = start_pos.x();
		if(flags & FTF_AlignHCenter)
			pos.x() += (max_sz.w() - line_size.width) / 2;
		else if(flags & FTF_AlignRight)
			pos.x() += max_sz.w() - line_size.width;

		for(;sbeg != line_size.end; ++sbeg)
		{
			if(*sbeg == '\n')
				continue;
			const font_entity&   reg = impl->load_char(*sbeg);
			const font_size      sz(char_width(*sbeg), height() * reg.v_scale);
			const font_rect      fp(font_pos(pos.x() + height() * reg.left, pos.y() + height() * reg.top), sz);

			if(last_texture != reg.tex)
			{
				add_job(chars_to_draw);
				last_texture = reg.tex;
			}

			vit = fill_sprite_vertices(vit, fp, reg.rect, 0);
			pos.x() += char_space(*sbeg);

			++chars_to_draw;
		}

		sz.w() = std::max(sz.w(), line_size.width);
		sz.h() += height();

		if(flags & FTF_NoMultiLine)
			break;

		sbeg = line_size.next_begin;

		pos.y() += height();
	}
	_lock.unlock();
	add_job(chars_to_draw);
	flush();
	return sz;
}

void sge::font::add_job(const size_type cur_index)
{
	jobs.push_back(job(last_texture, last_index, cur_index));
	last_index = cur_index;
}

sge::font_unit sge::font::char_width(const char_type ch) const
{
	const font_entity& entity = impl->load_char(ch);
	return height() * entity.h_scale;
}

sge::font_unit sge::font::char_space(const char_type ch) const
{
	const font_entity& entity = impl->load_char(ch);
	return height() * entity.x_advance;
}

sge::font::line_size_t sge::font::text_width_unformatted(string_type::const_iterator sbeg, const string_type::const_iterator send, const font_unit width) const
{
	font_unit w(0);
	for(; sbeg != send; ++sbeg)
	{
		if(*sbeg == '\n')
			continue;
		const font_unit delta = char_space(*sbeg);
		if(delta + w > width)
			break;
		w += delta;
	}
	return line_size_t(w,sbeg);
}

sge::font_size sge::font::text_size(string_type::const_iterator sbeg, const string_type::const_iterator send, const font_unit width, const font_flag_t flags) const
{
	if(flags & FTF_NoMultiLine)
		return font_size(text_width_unformatted(sbeg, send, width).width, height());

	font_size sz(0,0);
	while(sbeg != send)
	{
		const line_size_t line_size = line_width(sbeg, send, width, flags);
		const font_unit line_w = line_size.width;
		if(line_w == 0)
			break;
		sz.w() = std::max(sz.w(), line_w);
		sz.h() += height();
		sbeg = line_size.next_begin;
	}
	return sz;
}

sge::font_size sge::font::text_size(const string_type& s, const font_unit width, const font_flag_t flags) const
{
	return text_size(s.begin(),s.end(),width,flags);
}

sge::font::line_size_t sge::font::line_width(string_type::const_iterator sbeg, const string_type::const_iterator send, const font_unit width, const font_flag_t flags) const
{
	if(flags & FTF_NoMultiLine)
		return text_width_unformatted(sbeg, send, width);

	font_unit w(0), last_width(0);
	string_type::const_iterator last_white = sbeg;

	for(; sbeg != send; ++sbeg)
	{
		if(*sbeg == '\n')
			return line_size_t(w, ++sbeg);
		if(isspace_ucs4(*sbeg))
		{
			last_white = sbeg;
			last_width = w;
		}
		const font_unit nw = w + char_space(*sbeg);
		if(nw > width)
		{
			const font_unit ret_width =  last_width == 0 ? w : last_width;
			if(flags & FTF_NoLineWrap)
			{
				const string_type::const_iterator next_nl = std::find(sbeg, send, uchar_t('\n')),
				                                  next_begin = next_nl == send ? send : boost::next(next_nl);
				return line_size_t(ret_width, sbeg, next_begin);
			}
			return line_size_t(ret_width, last_width > 0 ? ++last_white : sbeg);
		}
		w = nw;
	}
	return line_size_t(w, send);
}

void sge::font::flush()
{
	// FIXME
//	std::sort(jobs.begin(), jobs.end(), boost::lambda::bind(&job::tex, boost::lambda::_1) < boost::lambda::bind(&job::tex, boost::lambda::_2));
	{
		lock_ptr<index_buffer_ptr> _lock(ib,LF_Discard);
		index_buffer::iterator iib = ib->begin();
		for(job_array::const_iterator it = jobs.begin(); it != jobs.end(); ++it)
			for(size_type i = it->first_index; i < it->end_index; ++i)
				iib = fill_sprite_indices(iib, i*4);
	}

	set_parameters();
	rend->set_texture(last_texture);
	for(job_array::const_iterator it = jobs.begin(); it != jobs.end(); ++it)
	{
		if(it->tex != last_texture)
		{
			rend->set_texture(it->tex);
			last_texture = it->tex;
		}
		rend->render(vb, ib, 0, vb->size(), PT_Triangle, (it->end_index - it->first_index)*2, it->first_index*6);
	}
	jobs.clear();
}

void sge::font::set_parameters()
{
	set_matrices();
	rend->set_bool_state(BS_EnableLighting,true);
	rend->set_bool_state(BS_EnableAlphaBlending,true);
	rend->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
}

sge::font::line_size_t::line_size_t(const font_unit width, const string_type::const_iterator end, const string_type::const_iterator next_begin)
 : width(width),
   end(end),
   next_begin(next_begin)
{}
	
sge::font::line_size_t::line_size_t(const font_unit width, const string_type::const_iterator end)
 : width(width),
   end(end),
   next_begin(end)
{}
