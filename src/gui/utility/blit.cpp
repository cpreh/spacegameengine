#include "blit.hpp"
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/assert.hpp>

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
	
	// Get sub view(s) and blit
	renderer::copy_and_convert_pixels(
		renderer::subimage_view(
			src,
			math::structure_cast<renderer::size_type>(
				is_translated_src)),
		renderer::subimage_view(
			dst,
			math::structure_cast<renderer::size_type>(
				is_translated_dst)));
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

	renderer::copy_and_convert_pixels(
		renderer::subimage_view(
			src,
			math::structure_cast<renderer::size_type>(
				src_trans)),
		renderer::subimage_view(
			dst,
			math::structure_cast<renderer::size_type>(
				clipped)));
}
