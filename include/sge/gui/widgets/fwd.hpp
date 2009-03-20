#ifndef SGE_GUI_WIDGETS_FWD_HPP_INCLUDED
#define SGE_GUI_WIDGETS_FWD_HPP_INCLUDED

#include <boost/mpl/vector.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class edit;
class label;
class graphics;
class backdrop;

namespace buttons
{
class text;
class image;
}

#define SGE_WIDGETS_APPLY(begin_func,func,end_func)\
	begin_func(sge::gui::widgets::edit)\
	func(sge::gui::widgets::label)\
	func(sge::gui::widgets::graphics)\
	func(sge::gui::widgets::backdrop)\
	func(sge::gui::widgets::buttons::text)\
	end_func(sge::gui::widgets::buttons::image)

#define SGE_WIDGETS_FWD_COMMA_WIDGET(w) w,
#define SGE_WIDGETS_FWD_NO_COMMA_WIDGET(w) w

typedef boost::mpl::vector<
	SGE_WIDGETS_APPLY(SGE_WIDGETS_FWD_COMMA_WIDGET,SGE_WIDGETS_FWD_COMMA_WIDGET,SGE_WIDGETS_FWD_NO_COMMA_WIDGET)
> types;
}
}
}

#endif
