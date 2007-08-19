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


#include <boost/next_prior.hpp>
#include "../../types.hpp"
#include "../renderer.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../types.hpp"
#include "../transform.hpp"
#include "../lock_ptr.hpp"
#include "../font.hpp"
#include "../../sprite/helper.hpp"

sge::font::font(const font_metrics_ptr metrics_, const font_drawer_ptr drawer_)
: metrics_(metrics_),
  drawer_(drawer_)
{}

sge::font_unit sge::font::height() const
{
	return metrics()->line_height();
}

sge::font_dim sge::font::draw_text(const string_type& text, const font_pos start_pos, const font_dim max_sz, const font_flag_t flags)
{
	if(text.empty() || height() > max_sz.h())
		return font_dim(0,0);
	font_pos pos = start_pos;
	if(flags & font_flags::align_vcenter || flags & font_flags::align_bottom)
	{
		const font_unit text_height = text_size(text.begin(), text.end(), max_sz.w(), flags).h();
		if(flags & font_flags::align_vcenter)
			pos.y() += (max_sz.h() - text_height) / 2;
		else if(flags & font_flags::align_bottom)
			pos.y() += max_sz.h() - text_height;
	}

	font_dim sz(0,0);
	string_type::const_iterator sbeg(text.begin());

	drawer()->begin_rendering(text.size());
	while(sbeg != text.end() && sz.h() + height() <= max_sz.h())
	{
		const line_size_t line_size = line_width(sbeg, text.end(), max_sz.w(), flags);

		pos.x() = start_pos.x();
		if(flags & font_flags::align_hcenter)
			pos.x() += (max_sz.w() - line_size.width) / 2;
		else if(flags & font_flags::align_right)
			pos.x() += max_sz.w() - line_size.width;

		for(;sbeg != line_size.end; ++sbeg)
		{
			if(*sbeg == '\n')
				break;
			const char_metric_ptr metric = metrics()->load_char(*sbeg);
			const font_rect fp(font_pos(pos.x() + metric->left(), pos.y() + metric->top()), font_dim(metric->width(), metric->height()));
			drawer()->draw_char(*sbeg, fp, metric->pixmap());

			pos.x() += char_space(*sbeg);
		}

		sz.w() = std::max(sz.w(), line_size.width);
		sz.h() += height();

		if(flags & font_flags::no_multi_line)
			break;

		sbeg = line_size.next_begin;

		pos.y() += height();
	}
	drawer()->end_rendering();
	return sz;
}

sge::font_dim sge::font::draw_text(const string_type& text, const pos2 pos, const math::dim2 max_size, const screen_size_t screen_size, const font_flag_t flags)
{
	return draw_text(text, space_size_to_pixel<font_pos>(pos, screen_size), space_size_to_pixel<font_dim>(max_size, screen_size), flags);
}

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

sge::font_dim sge::font::text_size(string_type::const_iterator sbeg, const string_type::const_iterator send, const font_unit width, const font_flag_t flags) const
{
	if(flags & font_flags::no_multi_line)
		return font_dim(text_width_unformatted(sbeg, send, width).width, height());

	font_dim sz(0,0);
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

sge::font_dim sge::font::text_size(const string_type& s, const font_unit width, const font_flag_t flags) const
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
				const string_type::const_iterator next_nl = std::find(sbeg, send, static_cast<string::value_type>('\n')),
				                                  next_begin = next_nl == send ? send : boost::next(next_nl);
				return line_size_t(ret_width, sbeg, next_begin);
			}
			return line_size_t(ret_width, last_width > 0 ? ++last_white : sbeg);
		}
		w = nw;
	}
	return line_size_t(w, send);
}

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
