/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../metrics.hpp"
#include "../glyph.hpp"
#include "../char_metric.hpp"
#include <sge/font/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <utility>

sge::freetype::metrics::metrics(
	library &_lib,
	sge::charconv::system_ptr const _conv_system,
	fcppt::filesystem::path const &_font_path,
	font::size_type const _font_height
)
:
	face_(
		_lib,
		_font_path
	),
	conv_system_(
		_conv_system
	),
	pixel_size_(
		_font_height
	),
	buffer_()
{
	if(
		::FT_Select_Charmap(
			face_.get(),
			FT_ENCODING_UNICODE
		)
		!= 0
	)
		throw sge::font::exception(
			FCPPT_TEXT("No Unicode code map found!")
		);

	if(
		::FT_Set_Pixel_Sizes(
			face_.get(),
			0,
			static_cast<
				FT_UInt
			>(
				_font_height
			)
		)
	)
		throw sge::font::exception(
			FCPPT_TEXT("FT_Set_Pixel_Sizes() failed!")
		);
}

sge::freetype::metrics::~metrics()
{}

sge::font::char_metric_ptr const
sge::freetype::metrics::load_char(
	font::char_type const _ch
)
{
	{
		buffer_type::const_iterator const it(
			buffer_.find(
				_ch
			)
		);

		if(
			it != buffer_.end()
		)
			return it->second;
	}

	font::char_metric_ptr const metric(
		fcppt::make_shared_ptr<
			freetype::char_metric
		>(
			fcppt::ref(
				face_
			),
			conv_system_,
			_ch
		)
	);

	buffer_.insert(
		std::make_pair(
			_ch,
			metric
		)
	);

	return metric;
}

sge::font::unit
sge::freetype::metrics::line_height() const
{
	return
		static_cast<
			font::unit
		>(
			face_->size->metrics.height
			/ 64
		);
}
