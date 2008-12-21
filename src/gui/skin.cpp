#include "utility/type_comparator.hpp"
#include <sge/gui/skin.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/events/fwd.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>

namespace
{
class call_draw
{
	public:
	typedef void result_type;

	call_draw(
		sge::gui::skin &s,
		sge::gui::events::invalid_area const &e) 
		: s(s),
		  e(e) {}

	template<typename V>
	//void operator()(V &v) { s.draw(v,e); }
	void operator()(V &) { }

	void value() const {}
	private:
	sge::gui::skin &s;
	sge::gui::events::invalid_area const &e;
};

class call_size_hint
{
	public:
	typedef sge::gui::dim result_type;

	call_size_hint(sge::gui::skin const &s) : s(s) {}

	template<typename V>
	void operator()(V const &v) { sh = s.size_hint(v); }

	sge::gui::dim const value() const { return sh; }
	private:
	sge::gui::skin const &s;
	sge::gui::dim sh;
};
}

void sge::gui::skin::draw(widget &w,events::invalid_area const &e)
{
	call_draw cd(*this,e);
	boost::function<void (widget &)> fn = 
		boost::bind(&skin::default_handler,this,_1,boost::ref(e));
	utility::type_comparator<widgets::types>(
		w,
		cd,
		fn);
}

//sge::gui::dim const sge::gui::skin::size_hint(widget const &w) const
sge::gui::dim const sge::gui::skin::size_hint(widget const &) const
{
	return dim();
	/*
	return utility::type_comparator<widgets::types>(
		w,
		call_size_hint(*this),
		boost::bind(&skin::default_hint_handler,this,_1));
		*/
}

void sge::gui::skin::default_handler(widget &,events::invalid_area const &)
{
	throw exception(SGE_TEXT("tried to draw a widget whose type is not drawable"));
}

sge::gui::dim const sge::gui::skin::default_hint_handler(widget const &)
{
	throw exception(SGE_TEXT("tried to hint a widget whose type is not drawable"));
}
