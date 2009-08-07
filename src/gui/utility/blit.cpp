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


#include "blit.hpp"
#include "normalization.hpp"
#include <sge/math/rect/intersection.hpp>
#include <sge/math/rect/structure_cast.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/algorithm/transform.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/assert.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <limits>
#include <algorithm>

#if 0
namespace
{
template<class DstPixel>
class channel_blitter 
{
public:
	typedef DstPixel pixel_type;
	typedef typename sge::image::color::channel<
		typename boost::remove_const<
			DstPixel
		>::type
	>::type channel_type;

	channel_blitter(
		pixel_type const &src,
		pixel_type const &dest,
		channel_type const src_alpha,
		channel_type const dest_alpha,
		pixel_type &result);

	template<class T>
	void operator()(T &) const;
private:
	pixel_type const &src,dest;
	channel_type const src_alpha,dest_alpha;
	pixel_type &result;
};

template<class DstPixel>
channel_blitter<DstPixel>::channel_blitter(
	pixel_type const &src,
	pixel_type const &dest,
	channel_type const src_alpha,
	channel_type const dest_alpha,
	pixel_type &result)
:
	src(src),
	dest(dest),
	src_alpha(src_alpha),
	dest_alpha(dest_alpha),
	result(result)
{}

template<class DstPixel>
template<class T>
void channel_blitter<DstPixel>::operator()(T &t) const
{
	if (t == 3)
	{
		if (src[t]+dest[t] > std::numeric_limits<channel_type>::max())
			result[t] = std::numeric_limits<channel_type>::max();
		else
			result[t] = static_cast<channel_type>(src[t]+dest[t]);
			
		return;
	}

	float const src_floating = sge::gui::utility::normalize<float>(src_alpha);
	float const dest_floating = sge::gui::utility::normalize<float>(dest_alpha);

	result[t] = static_cast<channel_type>(
		static_cast<float>(src[t])*src_floating+
		static_cast<float>(dest[t])*
			std::max(
				dest_floating-src_floating,
				0.0f));
}

class blitter
{
	public:
	template<
		typename Src,
		typename Dst
	>
	void operator()(
		Src const &src_color,
		Dst &dst_color) const;
};

template<
	typename Src,
	typename Dst
>
void
blitter::operator()(
	Src const &src_color,
	Dst &result) const
{
	boost::mpl::for_each<typename Dst::layout_t::channel_mapping_t>(
		channel_blitter<Dst>(
			sge::image::color::convert<Dst>(src_color),
			result,
			sge::image::color::convert<Dst>(src_color)[3],
			result[3],
			result));
}
}

void sge::gui::utility::blit_invalid(
	const_image_view const &src,
	rect const &src_rect,
	image_view const dst,
	rect const &dst_rect,
	bool transparency)
{
	// Calculate intersection of source and destination
	rect const is = intersection(
		src_rect,
		dst_rect);
	
	// No intersection? then leave now.
	if (is == rect::null())
		return;

	// Move intersection rect to origin of invalid rect
	rect const is_translated_dst(
		is.pos()-dst_rect.pos(),
		is.dim());

	rect const is_translated_src(
		is.pos()-src_rect.pos(),
		is.dim());

	if (transparency)
	{
		sge::image::algorithm::transform(
			sge::image::view::sub(
				src,
				math::rect::structure_cast<
					sge::image::rect
				>(
					is_translated_src
				)
			),
			sge::image::view::sub(
				dst,
				math::rect::structure_cast<
					sge::image::rect
				>(
					is_translated_dst
				)
			),
			blitter()
		);
	}
	else
	{
		sge::image::algorithm::copy_and_convert(
			sge::image::view::sub(
				src,
				math::rect::structure_cast<
					sge::image::rect
				>(
					is_translated_src
				)
			),
			sge::image::view::sub(
				dst,
				math::rect::structure_cast<
					sge::image::rect
				>(
					is_translated_dst
				)
			)
		);
	}
}

void sge::gui::utility::blit(
	const_image_view const &src,
	rect const &src_rect,
	image_view const dst,
	rect const &dst_rect,
	rect const &clip_rect)
{
	SGE_ASSERT(src_rect.dim() == dst_rect.dim());

	rect const clipped = intersection(
		dst_rect,
		clip_rect);
	
	rect const src_trans = rect(
		clipped.pos() - dst_rect.pos(),
		clipped.dim());

	sge::image::algorithm::transform(
		sge::image::view::sub(
			sge::image::view::sub(
				src,
				math::rect::structure_cast<
					sge::image::rect
				>(
					src_rect
				)
			),
			math::rect::structure_cast<
				sge::image::rect
			>(
				src_trans
			)
		),
		sge::image::view::sub(
			dst,
			math::rect::structure_cast<
				sge::image::rect
			>(
				clipped
			)
		),
		blitter()
	);
}

#endif
