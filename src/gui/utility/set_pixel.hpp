#ifndef SGE_GUI_UTILITY_SET_PIXEL_HPP_INCLUDED
#define SGE_GUI_UTILITY_SET_PIXEL_HPP_INCLUDED

#include <sge/gui/types.hpp>
#include <sge/renderer/any_color_convert.hpp>

namespace sge
{
namespace gui
{
namespace utility
{

class set_pixel {
public:
	typedef void result_type;

	explicit set_pixel(
		color const &src);
	
	template<
		typename Dest
	>
	void operator()(
		Dest const &) const;
private:
	color const src;
};

}
}
}

sge::gui::utility::set_pixel::set_pixel(
	color const &src)
:
	src(src)
{}

template<
	typename Dest
>
void sge::gui::utility::set_pixel::operator()(
	Dest const &d) const
{
	*d.at(0, 0)
		= renderer::any_color_convert<
			typename Dest::locator::value_type
		>(
			src);
		
}

#endif
