/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <locale>
#include <boost/next_prior.hpp>
#include "../../types.hpp"
#include "../renderer.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../types.hpp"
#include "../transform.hpp"
#include "../font.hpp"
#include "../../sprite/helper.hpp"
#include "../../math/rect_impl.hpp"

sge::font::font(const font_metrics_ptr metrics_, const font_drawer_ptr drawer_)
: metrics_(metrics_),
  drawer_(drawer_)
{}

sge::font_unit sge::font::height() const
{
	return metrics()->line_height();
}

const sge::font::text_size_t sge::font::draw_text(const string_type& text,
                                                  const font_pos start_pos,
                                                  const font_dim max_sz,
                                                  const font_align_h::type align_h,
                                                  const font_align_v::type align_v,
                                                  const font_flag_t flags) const
{
	if(text.empty() || height() > max_sz.h())
		return text_size_t(font_dim(0,0), text.begin(), text.begin());

	const text_size_t total_size = text_size(text.begin(), text.end(), max_sz, flags);

	font_pos pos = start_pos;
	switch(align_v) {
	case font_align_v::center:
		pos.y() += (max_sz.h() - total_size.size().h()) / 2;
		break;
	case font_align_v::bottom:
		pos.y() += max_sz.h() - total_size.size().h();
		break;
	case font_align_v::top:
		break;
	default:
		throw exception("Invalid font_align_v!");
	}

	string_type::const_iterator sbeg(text.begin());

	drawer()->begin_rendering(text.size(), total_size.size());
	while(sbeg != total_size.next_begin())
	{
		const text_size_t line_size = line_width(sbeg, text.end(), max_sz.w(), flags);

		pos.x() = start_pos.x();
		
		switch(align_h) {
		case font_align_h::center:
			pos.x() += (max_sz.w() - line_size.size().w()) / 2;
			break;
		case font_align_h::right:
			pos.x() += max_sz.w() - line_size.size().w();
			break;
		case font_align_h::left:
			break;
		default:
			throw exception("Invalid font_align_h!");
		}

		for(;sbeg != line_size.end(); ++sbeg)
		{
			const char_metric_ptr metric = metrics()->load_char(*sbeg);
			const font_rect fp(font_pos(pos.x() + metric->left(), pos.y() + metric->top()), font_dim(metric->width(), metric->height()));
			drawer()->draw_char(*sbeg, fp, metric->pixmap());

			pos.x() += char_space(*sbeg);
		}

		sbeg = line_size.next_begin();

		pos.y() += height();
	}
	drawer()->end_rendering();

	return total_size;
}

/*const sge::font::text_size_t sge::font::draw_text(const string_type& text, const pos2 pos, const math::dim2 max_size, const screen_size_t screen_size, const font_align_h::type align_h, const font_align_v::type align_v, const font_flag_t flags) const
{
	return draw_text(text, space_size_to_pixel<font_pos>(pos, screen_size), space_size_to_pixel<font_dim>(max_size, screen_size), align_h, align_v, flags);
}*/

sge::font_unit sge::font::char_space(const char_type ch) const
{
	return metrics()->load_char(ch)->x_advance();
}

const sge::font::text_size_t sge::font::text_size(string_type::const_iterator sbeg, const string_type::const_iterator send, const font_dim max_sz, const font_flag_t flags) const
{
	font_dim sz(0,0);
	while(sbeg != send && sz.h() + height() <= max_sz.h())
	{
		const text_size_t line_size = line_width(sbeg, send, max_sz.w(), flags);
		const font_unit line_w = line_size.size().w();
		sz.w() = std::max(sz.w(), line_w);
		sz.h() += height();
		sbeg = line_size.next_begin();

		if(flags & font_flags::no_multi_line)
			break;
	}
	return text_size_t(sz, sbeg, sbeg);
}

const sge::font::text_size_t sge::font::text_size(const string_type& s, const font_dim max_sz, const font_flag_t flags) const
{
	return text_size(s.begin(),s.end(),max_sz,flags);
}

const sge::font::text_size_t sge::font::line_width(string_type::const_iterator sbeg, const string_type::const_iterator send, const font_unit width, const font_flag_t flags) const
{
	font_unit w(0), last_width(0);
	string_type::const_iterator last_white = sbeg;

	for(; sbeg != send; ++sbeg)
	{
		if(*sbeg == '\n')
			return text_size_t(font_dim(w, height()), sbeg, boost::next(sbeg));

		if(std::isspace(*sbeg, std::locale()))
		{
			last_white = sbeg;
			last_width = w;
		}

		const font_unit nw = w + char_space(*sbeg);
		if(nw > width)
		{
			if(last_width && !(flags & font_flags::no_line_wrap))
				return text_size_t(font_dim(last_width, height()), last_white, boost::next(last_white));
			return text_size_t(font_dim(w, height()), sbeg, sbeg);
		}
		w = nw;
	}
	return text_size_t(font_dim(w, height()), send, send);
}

const sge::font_metrics_ptr sge::font::metrics() const
{
	return metrics_;
}

const sge::font_drawer_ptr sge::font::drawer() const
{
	return drawer_;
}

sge::font::text_size_t::text_size_t(const font_dim size_, const string_type::const_iterator end_, const string_type::const_iterator next_begin_)
 : size_(size_),
   end_(end_),
   next_begin_(next_begin_)
{}
	
sge::font_dim sge::font::text_size_t::size() const
{
	return size_;
}

sge::font::text_size_t::const_iterator sge::font::text_size_t::end() const
{
	return end_;
}

sge::font::text_size_t::const_iterator sge::font::text_size_t::next_begin() const
{
	return next_begin_;
}
