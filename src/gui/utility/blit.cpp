#include "blit.hpp"
#include "normalization.hpp"
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/transform_pixels.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/assert.hpp>
#include <sge/renderer/color_convert.hpp>
#include <sge/renderer/any_color_convert.hpp>
#include <sge/renderer/color_channel.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <limits>
#include <algorithm>

namespace
{
template<class DstPixel>
struct channel_blitter 
{
	typedef DstPixel pixel_type;
	typedef typename sge::renderer::color_channel<typename boost::remove_const<DstPixel>::type>::type channel_type;

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
: src(src),
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
			sge::renderer::color_convert<Dst>(src_color),
			result,
			sge::renderer::color_convert<Dst>(src_color)[3],
			result[3],
			result));
}
}

void sge::gui::utility::blit_invalid(
	const_image_view const &src,
	rect const &src_rect,
	image_view const dst,
	rect const &dst_rect)
{
	// Calculate intersection of source and destination
	rect const is = math::intersection(
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

	renderer::transform_pixels(
		renderer::subimage_view(
			src,
			math::structure_cast<renderer::lock_rect>(
				is_translated_src)),
		renderer::subimage_view(
			dst,
			math::structure_cast<renderer::lock_rect>(
				is_translated_dst)),
		blitter());
}

void sge::gui::utility::blit(
	const_image_view const &src,
	rect const &src_rect,
	image_view const dst,
	rect const &dst_rect,
	rect const &clip_rect)
{
	SGE_ASSERT(src_rect.dim() == dst_rect.dim());

	rect const clipped = math::intersection(
		dst_rect,
		clip_rect);
	
	rect const src_trans = rect(
		clipped.pos() - dst_rect.pos(),
		clipped.dim());

	renderer::transform_pixels(
		renderer::subimage_view(
			renderer::subimage_view(
				src,
				math::structure_cast<renderer::lock_rect>(
					src_rect)),
			math::structure_cast<renderer::lock_rect>(
				src_trans)),
		renderer::subimage_view(
			dst,
			math::structure_cast<renderer::lock_rect>(
				clipped)),
		blitter());
}
