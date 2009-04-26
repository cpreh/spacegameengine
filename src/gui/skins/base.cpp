/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "../utility/type_comparator.hpp"
#include "../utility/blit.hpp"
#include <sge/gui/skins/base.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/gui/events/fwd.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/unit.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <typeinfo>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skin"),
	false);
}

namespace
{
class call_draw
{
	public:
	typedef void result_type;

	call_draw(
		sge::gui::skins::base &s,
		sge::gui::events::invalid_area const &e) 
		: s(s),
		  e(e) {}

	template<typename V>
	void operator()(V &v) { s.draw(v,e); }

	void value() const {}
	private:
	sge::gui::skins::base &s;
	sge::gui::events::invalid_area const &e;
};

class call_optimal_size
{
	public:
	typedef sge::gui::dim result_type;

	call_optimal_size(
		sge::gui::skins::base const &s) : s(s) {}

	template<typename V>
	void operator()(V const &v) 
	{ 
		sh = s.optimal_size(v); 
	}

	sge::gui::dim const value() const { return sh; }
	private:
	sge::gui::skins::base const &s;
	sge::gui::dim sh;
};
}

SGE_GUI_SKIN_DRAW_RETURN(widgets::base) sge::gui::skins::base::draw(
	SGE_GUI_SKIN_DRAW_PARAMS_NAMED(widgets::base))
{
	if (typeid(w) == typeid(widgets::base))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("draw called for widget, falling back"));
		fallback(
			w,
			e);
		return;
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("draw called for some other widget"));

	utility::type_comparator<widgets::types>(
		w,
		call_draw(
			*this,
			e),
		boost::bind(
			&skins::base::default_handler,
			this,
			_1,
			boost::ref(e)));
}

SGE_GUI_SKIN_SIZE_RETURN(widgets::base) sge::gui::skins::base::optimal_size(
	SGE_GUI_SKIN_SIZE_PARAMS_NAMED(widgets::base)) const
{
	if (typeid(w) == typeid(widgets::base))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("optimal_size called for widget, returning null"));
		return dim::null();
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("optimal_size called for widgets::base ") 
		        << type_info(typeid(w)).name());

	return utility::type_comparator<widgets::types>(
		w,
		call_optimal_size(*this),
		boost::bind(&skins::base::default_hint_handler,this,_1));
}

SGE_GUI_SKIN_DRAW_RETURN(widgets::base) sge::gui::skins::base::default_handler(
	SGE_GUI_SKIN_DRAW_PARAMS(widgets::base))
{
	throw exception(SGE_TEXT("tried to draw a widgets::base whose type is not drawable"));
}

SGE_GUI_SKIN_SIZE_RETURN(widgets::base) sge::gui::skins::base::default_hint_handler(
	SGE_GUI_SKIN_SIZE_PARAMS(widgets::base)) const
{
	throw exception(SGE_TEXT("tried to hint a widgets::base whose type is not drawable"));
}
	
sge::gui::skins::base::~base()
{}

void sge::gui::skins::base::resize_buffer(
	widgets::base const &b)
{
	// resize internal buffer if neccessary
	if (b.size() != b.buffer().size())
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1
				<< SGE_TEXT("resizing from ") 
				<< b.buffer().size()
				<< SGE_TEXT(" to ")
				<< b.size());
		b.buffer().resize(
			b.size());
	}
}

void sge::gui::skins::base::blit_invalid(
	widgets::base const &w,
	canvas::object &c,
	events::invalid_area const &e,
	bool const t)
{
	utility::blit_invalid(
		renderer::make_const_image_view(c.view()),
		rect(w.absolute_pos(),c.size()),
		e.texture(),
		e.area(),
		t);
}
