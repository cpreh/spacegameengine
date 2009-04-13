#include <sge/gui/detail/managers/compiler.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/detail/managers/render.hpp>
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("managers: compiler"),
	false);
}

sge::gui::detail::managers::compiler::compiler(
	mouse &_mouse,
	render &_render)
	: mouse_(_mouse),
	  render_(_render)
{
}

void sge::gui::detail::managers::compiler::add(widget &/*w*/)
{
	//recompiles.insert(&w);
}

void sge::gui::detail::managers::compiler::remove(widget &w)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("deleting a widget of type ")
		        << typeid(w).name());

	// remove now dead references from recompile list
	for (recompile_container::iterator it = recompiles.begin(),next = it; 
		   it != recompiles.end(); 
		   it = next)
	{
		++next;

		if ((*it) == &w || has_parent(**it,w))
			recompiles.erase(it);
	}

	if (deleted.find(&w) != deleted.end())
		deleted.erase(&w);

	if (w.has_parent())
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("inserting parent to deleted list"));
		deleted.insert(&(w.parent_widget()));
	}
}

void sge::gui::detail::managers::compiler::update()
{
	if (recompiles.empty() && deleted.empty())
		return;
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("there is stuff to recompile"));

	BOOST_FOREACH(widget *w,recompiles)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("compiling widget of type ") 
			        << typeid(*w).name());

		w->compile();
		if (!w->has_parent())
		{
			render_.resize(
				*w,
				w->size());
			render_.reposition(
				*w,
				w->screen_pos());
		}
	}
	recompiles.clear();

	BOOST_FOREACH(widget *w,deleted)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("invalidating deleted widget's parent: ")
			        << typeid(*w).name());
		w->invalidate(*w);
	}
	deleted.clear();

	mouse_.recalculate_focus();
}

void sge::gui::detail::managers::compiler::invalidate(
	widget &w)
{
	recompiles.insert(&w);
}

bool sge::gui::detail::managers::compiler::has_parent(
	widget const &v,
	widget const &w)
{
	if (!v.has_parent())
		return false;
	
	if (&(v.parent_widget()) == &w)
		return true;
	
	return has_parent(
		v.parent_widget(),
		w);
}
