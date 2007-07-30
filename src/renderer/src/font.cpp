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
#include "../../unicode.hpp"
#include "../../sprite/helper.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/next_prior.hpp>

/*sge::font::font(const renderer_ptr rend, const font_system_ptr font_sys, const std::string& font_name, const unsigned quality_in_pixel)
 : default_transformable(rend, matrix_2d_to_3d(), math::matrix_orthogonal_xy()),
   rend(rend),
   impl(font_sys->create_font(rend, font_name, quality_in_pixel)),
   vb(rend->create_vertex_buffer(vertex_format().add(vertex_usage::pos).add(vertex_usage::tex), 200)),
   ib(rend->create_index_buffer(vb->size()*3/2))
{
	height_pixel_scale(1);
}*/

sge::font::font(const font_metrics_ptr metrics_, const font_drawer_ptr drawer_)
: metrics_(metrics_),
  drawer_(drawer_)
{}

sge::font_unit sge::font::height() const
{
	return metrics()->line_height();
}

sge::font_size sge::font::draw_text(const string_type& text, const font_pos start_pos, const font_size max_sz, const color col, const font_flag_t flags)
{
	if(text.empty() || height() > max_sz.h())
		return font_size(0,0);
/*	last_index = 0;
	last_texture = impl->load_char(text[0]).tex;

	const vertex_buffer::size_type vbsize = text.size()*4;
	const index_buffer::size_type ibsize = text.size()*6;

	if(vb->size() < vbsize)
		vb->resize(vbsize);

	if(ib->size() < ibsize)
		ib->resize(ibsize);*/

	font_pos pos = start_pos;
	if(flags & font_flags::align_vcenter || flags & font_flags::align_bottom)
	{
		const font_unit text_height = text_size(text.begin(), text.end(), max_sz.w(), flags).h();
		if(flags & font_flags::align_vcenter)
			pos.y() += (max_sz.h() - text_height) / 2.f;
		else if(flags & font_flags::align_bottom)
			pos.y() += max_sz.h() - text_height;
		if(pos.y() < start_pos.y())
			pos.y() = start_pos.y();
	}

//	rend->set_color_state(color_state::ambient_light_color,col);

	font_size sz(0,0);
	string_type::const_iterator sbeg(text.begin());

//	lock_ptr<vertex_buffer_ptr> _lock(vb);
//	vertex_buffer::iterator vit = vb->begin();

//	std::size_t chars_to_draw = 0;
	while(sbeg != text.end() && sz.h() + height() <= max_sz.h())
	{
		const line_size_t line_size = line_width(sbeg, text.end(), max_sz.w(), flags);
		if(line_size.width == 0)
			break;

		pos.x() = start_pos.x();
		if(flags & font_flags::align_hcenter)
			pos.x() += (max_sz.w() - line_size.width) / 2;
		else if(flags & font_flags::align_right)
			pos.x() += max_sz.w() - line_size.width;

		for(;sbeg != line_size.end; ++sbeg)
		{
			if(*sbeg == '\n')
				continue;
			const char_metric_ptr metric = metrics()->load_char(*sbeg);
//			const font_entity&   reg = impl->load_char(*sbeg);
//			const font_size      sz(char_width(*sbeg), height() * reg.v_scale);
//			const font_rect      fp(font_pos(pos.x() + height() * reg.left, pos.y() + height() * reg.top), sz);

/*			if(last_texture != reg.tex)
			{
				add_job(chars_to_draw);
				last_texture = reg.tex;
			}

			vit = fill_sprite_vertices(vit, fp, reg.rect, 0);*/

			drawer()->draw_char(metric, pos, height(), col);

			pos.x() += char_space(*sbeg);

		//	++chars_to_draw;
		}

		sz.w() = std::max(sz.w(), line_size.width);
		sz.h() += height();

		if(flags & font_flags::no_multi_line)
			break;

		sbeg = line_size.next_begin;

		pos.y() += height();
	}
//	_lock.unlock();
//	add_job(chars_to_draw);
//	flush();
	return sz;
}

/*void sge::font::add_job(const size_type cur_index)
{
	jobs.push_back(job(last_texture, last_index, cur_index));
	last_index = cur_index;
}*/

/*sge::font_unit sge::font::char_width(const char_type ch) const
{
	const font_entity& entity = impl->load_char(ch);
	return height() * entity.h_scale;
}*/

sge::font_unit sge::font::char_space(const char_type ch) const
{
	return metrics()->load_char(ch)->x_advance();
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
	if(flags & font_flags::no_multi_line)
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
	if(flags & font_flags::no_multi_line)
		return text_width_unformatted(sbeg, send, width);

	font_unit w(0), last_width(0);
	string_type::const_iterator last_white = sbeg;

	for(; sbeg != send; ++sbeg)
	{
		if(*sbeg == '\n')
			return line_size_t(w, ++sbeg);
		if(isspace(*sbeg))
		{
			last_white = sbeg;
			last_width = w;
		}
		const font_unit nw = w + char_space(*sbeg);
		if(nw > width)
		{
			const font_unit ret_width =  last_width == 0 ? w : last_width;
			if(flags & font_flags::no_line_wrap)
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

/*void sge::font::flush()
{
	// FIXME
//	std::sort(jobs.begin(), jobs.end(), boost::lambda::bind(&job::tex, boost::lambda::_1) < boost::lambda::bind(&job::tex, boost::lambda::_2));
	{
		lock_ptr<index_buffer_ptr> _lock(ib);
		index_buffer::iterator iib = ib->begin();
		for(job_array::const_iterator it = jobs.begin(); it != jobs.end(); ++it)
			for(size_type i = it->first_index; i < it->end_index; ++i)
				iib = fill_sprite_indices(iib, static_cast<index_buffer::value_type>(i*4));
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
		rend->render(vb, ib, 0, vb->size(), indexed_primitive_type::triangle, (it->end_index - it->first_index)*2, it->first_index*6);
	}
	jobs.clear();
}

void sge::font::set_parameters()
{
	set_matrices();
	rend->set_bool_state(bool_state::enable_lighting,true);
	rend->set_bool_state(bool_state::enable_alpha_blending,true);
	rend->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
}*/

sge::font_metrics_ptr sge::font::metrics() const
{
	return metrics_;
}

sge::font_drawer_ptr sge::font::drawer() const
{
	return drawer_;
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
