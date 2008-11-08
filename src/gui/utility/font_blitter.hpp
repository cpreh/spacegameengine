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
template<class DstPixel,class FontPixel>
class font_blitter
{
	public:
	//typedef boost::gil::pixel<Channel,Layout> pixel_type;  
	typedef DstPixel dest_pixel_type;  
	typedef FontPixel font_pixel_type;  

	font_blitter(dest_pixel_type font_color);

	dest_pixel_type const operator()(
		dest_pixel_type const &src_color,
		font_pixel_type const &font_value) const;
	
	private:
	dest_pixel_type const font_color;
};
}
}
}

template<class DstPixel,class FontPixel>
sge::gui::utility::font_blitter<DstPixel,FontPixel>::font_blitter(
	dest_pixel_type const font_color)
	: font_color(font_color)
{
}

template<class DstPixel,class FontPixel>
typename sge::gui::utility::font_blitter<DstPixel,FontPixel>::dest_pixel_type const 
	sge::gui::utility::font_blitter<DstPixel,FontPixel>::operator()(
		dest_pixel_type const &src_color,
		font_pixel_type const &font_value) const
{
	dest_pixel_type result;

	boost::mpl::for_each<typename dest_pixel_type::layout_t::channel_mapping_t>(
		font_channel_blitter<dest_pixel_type>(
			src_color,
			font_color,
			result));

	return result;
}

#endif
