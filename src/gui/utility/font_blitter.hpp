#ifndef SGE_GUI_UTILITY_FONT_BLITTER_HPP_INCLUDED
#define SGE_GUI_UTILITY_FONT_BLITTER_HPP_INCLUDED

#include "font_channel_blitter.hpp"
#include <sge/font/types.hpp>
#include <boost/gil/pixel.hpp>
#include <boost/mpl/for_each.hpp>

namespace sge
{
namespace gui
{
namespace utility
{
template<class DstPixel>
class font_blitter
{
	public:
	typedef DstPixel dest_pixel_type;  

	font_blitter(dest_pixel_type font_color);

	template<class Dest,class Font>
	operator()(
		Dest const &src_color,
		Font const &font_value) const;
	private:
	dest_pixel_type const font_color;
};
}
}
}

template<class DstPixel>
sge::gui::utility::font_blitter<DstPixel>::font_blitter(
	dest_pixel_type const font_color)
	: font_color(font_color)
{
}

template<class DstPixel>
template<class Dest,class Font>
typename sge::gui::utility::font_blitter<DstPixel>::dest_pixel_type const 
	sge::gui::utility::font_blitter<DstPixel>::operator()(
		Dest const &src_color,
		Font const &font_value) const
{
	Dest result;

	boost::mpl::for_each<typename Dest::layout_t::channel_mapping_t>(
		font_channel_blitter<Dest>(
			src_color,
			font_color,
			result));

	return result;
}

#endif
