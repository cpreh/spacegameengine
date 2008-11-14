#ifndef SGE_GUI_UTILITY_FONT_BLITTER_HPP_INCLUDED
#define SGE_GUI_UTILITY_FONT_BLITTER_HPP_INCLUDED

#include "font_channel_blitter.hpp"
#include <sge/gui/types.hpp>
#include <boost/mpl/for_each.hpp>

namespace sge
{
namespace gui
{
namespace utility
{

class font_blitter
{
	public:
	typedef color dest_pixel_type;  

	explicit font_blitter(
		dest_pixel_type font_color);

	template<
		typename Dst,
		typename Src1,
		typename Src2
	>
	void operator()(
		Dst &dst_color,
		Src1 const &src_color,
		Src2 const &font_value) const;
	
	private:
	dest_pixel_type const font_color;
};
}
}
}

sge::gui::utility::font_blitter::font_blitter(
	dest_pixel_type const font_color)
	: font_color(font_color)
{
}

template<
	typename Dst,
	typename Src1,
	typename Src2
>
void
sge::gui::utility::font_blitter::operator()(
	Dst &,
	Src1 const &/*src_color*/,
	Src2 const &/*font_value*/) const
{
	/*
	dest_pixel_type result;

	boost::mpl::for_each<typename dest_pixel_type::layout_t::channel_mapping_t>(
		font_channel_blitter<dest_pixel_type>(
			src_color,
			font_color,
			result));

	return result;*/
}

#endif
