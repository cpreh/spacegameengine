#include "dispatch_type.hpp"
#include <sge/gui/skin.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>

namespace
{
struct draw_functor
{
	draw_functor(
		skin &s,
		widget &w,
		events::invalid_area const &e,
		boost::function<void (widget &,events::invalid_area const &)> fn)
	{}

	
};
}

void sge::gui::skin::draw(widget &w,events::invalid_area const &e)
{
	boost::mpl::for_each<widgets::types>(
		draw_functor(
			*this,
			w,
			e,
			boost::bind(&skin::default_handler,this,_1,_2)));

	dispatch_type<widgets::types,void>(
		*this,
		w,
		e,
		boost::bind(&skin::default_handler,this,_1,_2));
}

void sge::gui::skin::default_handler(widget &,events::invalid_area const &)
{
	throw exception(SGE_TEXT("tried to draw a widget whose type is not drawable"));
}
