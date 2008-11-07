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
class font_blitter
{
	template<class Channel,class Layout>
	boost::gil::pixel<Channel,Layout> const operator()(
		boost::gil::pixel<Channel,Layout> const &src_color,
		boost::gil::pixel<Channel,Layout> const &font_color,
		sge::font::color const &font_value) const;
};
}
}
}

template<class Channel,class Layout>
boost::gil::pixel<Channel,Layout> const sge::gui::utility:font_blitter::operator()(
	boost::gil::pixel<Channel,Layout> const &src_color,
	boost::gil::pixel<Channel,Layout> const &font_color,
	sge::font::color const &font_value) const
{
	typedef boost::gil::pixel<Channel,Layout> pixel_type;

	pixel_type result;

	boost::mpl::for_each<typename pixel_type::layout_t::channel_mapping_t>(
		font_channel_blitter<pixel_type>(src_color,font_color,result));

	return result;
}

#endif
