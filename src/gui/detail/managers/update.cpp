#include <sge/gui/detail/managers/update.hpp>
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
	SGE_TEXT("managers: update"),
	false);
}

sge::gui::detail::managers::update::update(
	mouse &_mouse,
	render &_render)
	: mouse_(_mouse),
	  render_(_render)
{
}

void sge::gui::detail::managers::update::add(widget &w)
{
	recompiles.insert(&w);
}

void sge::gui::detail::managers::update::remove(widget &w)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("deleting a widget"));

	// remove now dead references from recompile list
	for (recompile_container::iterator it = recompiles.begin(),next = it; 
		   it != recompiles.end(); 
		   it = next)
	{
		++next;

		if ((*it) == &w || has_parent(**it,w))
			recompiles.erase(it);
	}

	// if there is a parent, set it to recompile
	if (w.has_parent())
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("for the widget to delete there is a parent, so recompiling"));
		recompiles.insert(&(w.parent_widget()));
	}
}

void sge::gui::detail::managers::update::draw()
{
	if (recompiles.empty())
		return;
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("there is stuff to recompile"));

	// The standard behaviour for widgets which need recompiling is to determine
	// their topmost parent (a bit of overkill but it doesn't happen very often anyway); 
	// then, each parent is recompiled completely
	recompile_container parents;

	BOOST_FOREACH(widget *w,recompiles)
	{
		/*
		widget *parent = 0,*it = w;
		while (it != 0)
		{
			parent = it;
			it = it->parent_widget();
		}

		SGE_ASSERT(parent != 0);
		parents.insert(parent);
		*/
		parents.insert(&(w->oldest_parent()));
	}

	BOOST_FOREACH(widget *w,parents)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("compiling widget of type ") 
			        << typeid(w).name());

		w->compile();
		render_.resize(
			*w,
			w->size());
		render_.reposition(
			*w,
			w->screen_pos());
	}

	mouse_.recalculate_focus();
	recompiles.clear();
}

bool sge::gui::detail::managers::update::has_parent(
	widget const &v,
	widget const &w)
{
	if (!v.has_parent())
		return false;
	
	if (&(v.parent_widget()) == &w)
		return true;
	
	return has_parent(v.parent_widget(),w);
}
