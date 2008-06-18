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


#include <sge/font/font.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/exception.hpp>
#include <boost/next_prior.hpp>
#include <locale>

sge::font::font::font(
	const metrics_ptr metrics_,
	const drawer_ptr drawer_)
: metrics_(metrics_),
  drawer_(drawer_)
{}

sge::font::unit sge::font::font::height() const
{
	return metrics()->line_height();
}

const sge::font::text_size_t
sge::font::font::draw_text(
	const string& text,
	const pos start_pos,
	const dim max_sz,
	const align_h::type align_h,
	const align_v::type align_v,
	const flag_t flags) const
{
	if(text.empty() || height() > max_sz.h())
		return text_size_t(dim(0,0), text.begin(), text.begin());

	const text_size_t total_size = text_size(text.begin(), text.end(), max_sz, flags);

	pos pos_ = start_pos;
	switch(align_v) {
	case align_v::center:
		pos_.y() += (max_sz.h() - total_size.size().h()) / 2;
		break;
	case align_v::bottom:
		pos_.y() += max_sz.h() - total_size.size().h();
		break;
	case align_v::top:
		break;
	default:
		throw exception(SGE_TEXT("Invalid font::align_v!"));
	}

	string::const_iterator sbeg(text.begin());

	drawer()->begin_rendering(text.size(), total_size.size());
	while(sbeg != total_size.next_begin())
	{
		const text_size_t line_size = line_width(sbeg, text.end(), max_sz.w(), flags);

		pos_.x() = start_pos.x();
		
		switch(align_h) {
		case align_h::center:
			pos_.x() += (max_sz.w() - line_size.size().w()) / 2;
			break;
		case align_h::right:
			pos_.x() += max_sz.w() - line_size.size().w();
			break;
		case align_h::left:
			break;
		default:
			throw exception(SGE_TEXT("Invalid font::align_h!"));
		}

		for(;sbeg != line_size.end(); ++sbeg)
		{
			drawer()->draw_char(
				*sbeg,
				pos_,
				/*rect(
					pos(
						pos_.x() + metric->left(),
						pos_.y() + metric->top()),
					dim(
						metric->width(),
						metric->height())),*/
				metrics()->load_char(*sbeg)->pixmap());
			pos_.x() += char_space(*sbeg);
		}

		sbeg = line_size.next_begin();

		pos_.y() += height();
	}
	drawer()->end_rendering();

	return total_size;
}

sge::font::unit sge::font::font::char_space(const char_type ch) const
{
	return metrics()->load_char(ch)->x_advance();
}

const sge::font::text_size_t
sge::font::font::text_size(
	string::const_iterator sbeg,
	const string::const_iterator send,
	const dim max_sz,
	const flag_t flags) const
{
	dim sz(0,0);
	while(sbeg != send && sz.h() + height() <= max_sz.h())
	{
		const text_size_t line_size = line_width(sbeg, send, max_sz.w(), flags);
		const unit line_w = line_size.size().w();
		sz.w() = std::max(sz.w(), line_w);
		sz.h() += height();
		sbeg = line_size.next_begin();

		if(flags & flags::no_multi_line)
			break;
	}
	return text_size_t(sz, sbeg, sbeg);
}

const sge::font::text_size_t
sge::font::font::text_size(
	const string& s,
	const dim max_sz,
	const flag_t flags) const
{
	return text_size(
		s.begin(),
		s.end(),
		max_sz,
		flags);
}

const sge::font::text_size_t
sge::font::font::line_width(
	string::const_iterator sbeg,
	const string::const_iterator send,
	const unit width,
	const flag_t flags) const
{
	unit w(0), last_width(0);
	string::const_iterator last_white = sbeg;

	for(; sbeg != send; ++sbeg)
	{
		if(*sbeg == SGE_TEXT('\n'))
			return text_size_t(dim(w, height()), sbeg, boost::next(sbeg));

		if(std::isspace(*sbeg, std::locale()))
		{
			last_white = sbeg;
			last_width = w;
		}

		const unit nw = w + char_space(*sbeg);
		if(nw > width)
			return last_width && !(flags & flags::no_line_wrap)
				? text_size_t(dim(last_width, height()), last_white, boost::next(last_white))
				: text_size_t(dim(w, height()), sbeg, sbeg);
		w = nw;
	}
	return text_size_t(dim(w, height()), send, send);
}

const sge::font::metrics_ptr
sge::font::font::metrics() const
{
	return metrics_;
}

const sge::font::drawer_ptr
sge::font::font::drawer() const
{
	return drawer_;
}
