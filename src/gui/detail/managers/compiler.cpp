#include <sge/gui/detail/managers/compiler.hpp>
#include <sge/gui/widgets/base.hpp>
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

bool has_parent(
	sge::gui::widgets::base const &v,
	sge::gui::widgets::base const &w)
{
	if (!v.has_parent())
		return false;
	
	if (&(v.parent_widget()) == &w)
		return true;
	
	return has_parent(
		v.parent_widget(),
		w);
}

}

sge::gui::detail::managers::compiler::compiler(
	mouse &_mouse,
	render &_render)
	: mouse_(_mouse),
	  render_(_render)
{
}

void sge::gui::detail::managers::compiler::add(widgets::base &w)
{
	// since we cannot assume that widgets::base is fully constructed (just the base
	// class: widget), we defer invalidation to a later point of time
	invalidates.insert(&w);
}

void sge::gui::detail::managers::compiler::remove(widgets::base &w)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("deleting a widgets::base of type ")
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

	// we don't want to do anything with the widgets::base or it's parent right now
	// because any action could fall back to 'w' at some point, so we just make
	// an entry in the invalidated list which is iterated later
	
	// this could happen if a child of 'w' was deleted.
	if (invalidates.find(&w) != invalidates.end())
		invalidates.erase(&w);

	if (w.has_parent())
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("inserting parent to invalidates list"));
		invalidates.insert(&(w.parent_widget()));
	}
}

void sge::gui::detail::managers::compiler::update()
{
	if (recompiles.empty() && invalidates.empty())
		return;
	
	// the parents of invalidates widgets can now be safely invalidated
	BOOST_FOREACH(widgets::base *w,invalidates)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("invalidating widget's parent: ")
			        << typeid(*w).name());
		w->invalidate(*w);
	}
	invalidates.clear();

	BOOST_FOREACH(widgets::base *w,recompiles)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("compiling widgets::base of type ") 
			        << typeid(*w).name());
		w->compile();
	}
	recompiles.clear();

	mouse_.recalculate_focus();
}

void sge::gui::detail::managers::compiler::invalidate(
	widgets::base &w)
{
	recompiles.insert(&w);
}
