#ifndef SGE_GUI_UTILITY_FONT_CHANNEL_BLITTER_HPP_INCLUDED
#define SGE_GUI_UTILITY_FONT_CHANNEL_BLITTER_HPP_INCLUDED

#include <sge/font/types.hpp>
#include <sge/renderer/color_channel.hpp>

namespace sge
{
namespace gui
{
namespace utility
{
template<class DstPixel>
struct font_channel_blitter 
{
	font_channel_blitter(
		DstPixel const &bgcolor,
		DstPixel const &fontcolor,
		sge::font::color const &font,
		DstPixel &result);

	template<class T>
	void operator()(T &) const;
private:
	DstPixel const &bgcolor,fontcolor;
	sge::font::color const &font;
	DstPixel &result;
};
}
}
}

template<class DstPixel>
sge::gui::utility::font_channel_blitter<DstPixel>::font_channel_blitter(
	DstPixel const &bgcolor,
	DstPixel const &fontcolor,
	sge::font::color const &font,
	DstPixel &result)
: bgcolor(bgcolor),
  fontcolor(fontcolor),
  font(font),
	result(result)
{}

template<class DstPixel>
template<class T>
void sge::gui::utility::font_channel_blitter<DstPixel>::operator()(T &t) const
{
	float const font_value = static_cast<float>(font)/255.0f;
	result[t] = static_cast<typename renderer::color_channel<DstPixel>::type>(
		static_cast<float>(fontcolor[t])*font_value+
		static_cast<float>(bgcolor[t])*(1.0f-font_value));
}

#endif
