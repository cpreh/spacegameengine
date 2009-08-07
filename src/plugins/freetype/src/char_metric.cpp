/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../freetype.hpp"
#include "../face.hpp"
#include "../glyph.hpp"
#include "../char_metric.hpp"
#include <sge/image/algorithm/transform.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/optional_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <ostream>

namespace
{

struct converter {
	typedef void result_type;
	
	template<
		typename Src,
		typename Dest
	>
	result_type
	operator()(
		Src const &,//src,
		Dest const &dest
	) const
	{
		dest = sge::image::color::rgba8(
			sge::image::color::init::red %= 1.0,
			sge::image::color::init::blue %= 1.0,
			sge::image::color::init::green %= 1.0,
			sge::image::color::init::alpha %= 1.0);
//				static_cast<typename Dest::layout::channel_type>(src. template get<mizuiro::color::channel::gray>())
//		);
	}
};

}

sge::freetype::char_metric::char_metric(
	face &face_,
	char_type const ch)
:
	buffer(),
	offset_()
{
	if(FT_Load_Char(face_.get(), ch, FT_LOAD_DEFAULT))
		throw exception(SGE_TEXT("FT_Load_Glyph() failed!"));

	glyph glyph_(face_);
	FT_BitmapGlyph bmp_glyph = glyph_.bitmap_glyph();

	FT_Bitmap& bitmap = bmp_glyph->bitmap;
	
	offset_.x() = bmp_glyph->left;
	offset_.y() = static_cast<font::unit>(face_->size->metrics.ascender / 64 - bmp_glyph->top);
	x_advance_ = static_cast<font::unit>(face_->glyph->advance.x / 64);

	// FIXME: fix offsets and maybe those warnings
	if(offset_.x() < 0)
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("x offset of character '")
				<< ch
				<< SGE_TEXT("' is ")
				<< offset_.x()
				<< SGE_TEXT('!'));
	if(offset_.y() < 0)
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("y offset of character '")
				<< ch
				<< SGE_TEXT("' is ")
				<< offset_.y()
				<< SGE_TEXT('!'));

	buffer_type::dim_type const dim(
		bitmap.width,
		bitmap.rows
	);

	buffer = buffer_type(
		dim
	);

	sge::image::algorithm::transform(
		sge::image::view::make(
			static_cast<
				unsigned char const *
			>(
				bitmap.buffer
			),
			dim,
			sge::image::color::format::gray8,
			bitmap.pitch
		),
		buffer.view(),
		boost::bind(
			converter(),
			_1,
			_2
		)
	);
}

sge::freetype::char_metric::~char_metric()
{}

sge::font::pos const
sge::freetype::char_metric::offset() const
{
	return offset_;
}

sge::font::const_image_view const
sge::freetype::char_metric::pixmap() const
{
	return image::view::const_object(
		buffer.view()
	);
}

sge::font::unit
sge::freetype::char_metric::x_advance() const
{
	return x_advance_;
}
