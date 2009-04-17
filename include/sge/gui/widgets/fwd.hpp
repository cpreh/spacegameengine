#ifndef SGE_GUI_WIDGETS_FWD_HPP_INCLUDED
#define SGE_GUI_WIDGETS_FWD_HPP_INCLUDED

#include <boost/mpl/vector.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class base;
class edit;
class label;
class graphics;
class backdrop;

namespace buttons
{
class text;
class image;
}

#define SGE_GUI_WIDGETS_FWD_APPLY(begin_func,func,end_func)\
	begin_func(edit)\
	func(label)\
	func(graphics)\
	func(backdrop)\
	func(buttons::text)\
	end_func(buttons::image)

#define SGE_GUI_WIDGETS_FWD_COMMA_WIDGET(w) w,
#define SGE_GUI_WIDGETS_FWD_NO_COMMA_WIDGET(w) w

typedef boost::mpl::vector<
	SGE_GUI_WIDGETS_FWD_APPLY(SGE_GUI_WIDGETS_FWD_COMMA_WIDGET,SGE_GUI_WIDGETS_FWD_COMMA_WIDGET,SGE_GUI_WIDGETS_FWD_NO_COMMA_WIDGET)
> types;
}
}
}

#endif
