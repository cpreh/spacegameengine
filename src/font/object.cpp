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


#include <sge/font/object.hpp>
#include <sge/font/char_metric.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/drawer.hpp>
#include <sge/font/text_size.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/next_prior.hpp>
#include <locale>

sge::font::object::object(
	metrics_ptr const metrics_,
	drawer_ptr const drawer_)
:
	metrics_(metrics_),
	drawer_(drawer_)
{}

sge::font::object::~object()
{}

sge::font::unit
sge::font::object::height() const
{
	return metrics()->line_height();
}

sge::font::text_size const
sge::font::object::draw_text(
	string const &text,
	pos const &start_pos,
	dim const &max_sz,
	align_h::type const align_h,
	align_v::type const align_v,
	flag_t const flags) const
{
	if(!drawer())
		throw exception(
			SGE_TEXT("font::drawer not set in font::draw_text!"));

	if(text.empty() || height() > max_sz.h())
		return font::text_size(
			dim::null(),
			text.begin(),
			text.begin());

	font::text_size const total_size(
		text_size(
			text.begin(),
			text.end(),
			max_sz,
			flags
		)
	);

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

	drawer()->begin_rendering(text.size(), pos_, total_size.size());

	while(sbeg != total_size.next_begin())
	{
		font::text_size const line_size = line_width(sbeg, text.end(), max_sz.w(), flags);

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
			char_metric_ptr const cm(metrics()->load_char(*sbeg));
			drawer()->draw_char(
				*sbeg,
				pos_ + cm->offset(),
				cm->pixmap());
			pos_.x() += char_space(*sbeg);
		}

		sbeg = line_size.next_begin();

		pos_.y() += height();
	}
	drawer()->end_rendering();

	return total_size;
}

sge::font::unit
sge::font::object::char_space(
	char_type const ch) const
{
	return metrics()->load_char(ch)->x_advance();
}

sge::font::text_size const
sge::font::object::text_size(
	string::const_iterator sbeg,
	string::const_iterator const send,
	dim const &max_sz,
	flag_t const flags) const
{
	dim sz(dim::null());

	while(sbeg != send && sz.h() + height() <= max_sz.h())
	{
		font::text_size const line_size = line_width(sbeg, send, max_sz.w(), flags);
		unit const line_w = line_size.size().w();
		sz.w() = std::max(sz.w(), line_w);
		sz.h() += height();
		sbeg = line_size.next_begin();

		if(flags & flags::no_multi_line)
			break;
	}
	return font::text_size(sz, sbeg, sbeg);
}

sge::font::text_size const
sge::font::object::text_size(
	string const &s,
	dim const &max_sz,
	flag_t const flags) const
{
	return text_size(
		s.begin(),
		s.end(),
		max_sz,
		flags);
}

sge::font::text_size const
sge::font::object::line_width(
	string::const_iterator sbeg,
	string::const_iterator const send,
	unit const width,
	flag_t const flags) const
{
	unit w(0), last_width(0);
	string::const_iterator last_white = sbeg;

	for(; sbeg != send; ++sbeg)
	{
		if(*sbeg == SGE_TEXT('\n'))
			return font::text_size(dim(w, height()), sbeg, boost::next(sbeg));

		if(std::isspace(*sbeg, std::locale()))
		{
			last_white = sbeg;
			last_width = w;
		}

		const unit nw = w + char_space(*sbeg);
		if(nw > width)
			return last_width && !(flags & flags::no_line_wrap)
				? font::text_size(
					dim(
						last_width,
						height()
					),
					last_white,
					boost::next(
						last_white
					)
				)
				: font::text_size(
					dim(
						w,
						height()
					),
					sbeg,
					sbeg
				);
		w = nw;
	}
	return font::text_size(
		dim(
			w,
			height()
		),
		send,
		send
	);
}

sge::font::metrics_ptr const
sge::font::object::metrics() const
{
	return metrics_;
}

sge::font::drawer_ptr const
sge::font::object::drawer() const
{
	return drawer_;
}
