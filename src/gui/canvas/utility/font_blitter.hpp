#ifndef SGE_GUI_UTILITY_FONT_BLITTER_HPP_INCLUDED
#define SGE_GUI_UTILITY_FONT_BLITTER_HPP_INCLUDED

#include "font_channel_blitter.hpp"
#include <sge/renderer/color_convert.hpp>
#include <sge/renderer/any_color_convert.hpp>
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
	explicit font_blitter(
		color const &font_color);

	template<
		typename Font,
		typename Src,
		typename Dst
	>
	void operator()(
		Font const &font_value,
		Src const &src_color,
		Dst &dst_color) const;
	
	private:
	color const font_color;
};
}
}
}

sge::gui::utility::font_blitter::font_blitter(
	color const &font_color)
	: font_color(font_color)
{
}

template<
	typename Font,
	typename Src,
	typename Dst
>
void
sge::gui::utility::font_blitter::operator()(
	Font const &font_value,
	Src const &src_color,
	Dst &result) const
{
	boost::mpl::for_each<typename Dst::layout_t::channel_mapping_t>(
		font_channel_blitter<Dst,Font>(
			renderer::color_convert<Dst>(src_color),
			renderer::any_color_convert<Dst>(font_color),
			font_value,
			result));
}

#endif
