#include <sge/gui/detail/update_manager.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/widgets/container.hpp>
#include <sge/gui/detail/render_manager.hpp>
#include <sge/gui/detail/mouse_manager.hpp>
#include <boost/foreach.hpp>

sge::gui::detail::update_manager::update_manager(
	mouse_manager &mouse,
	render_manager &render)
	: mouse(mouse),
	  render(render)
{
}

void sge::gui::detail::update_manager::add(widget &w)
{
	recompiles.insert(&w);
}

void sge::gui::detail::update_manager::remove(widget &w)
{
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
	if (w.parent_widget())
		recompiles.insert(w.parent_widget());
}

void sge::gui::detail::update_manager::draw()
{
	if (recompiles.empty())
		return;

	// The standard behaviour for widgets which need recompiling is to determine
	// their topmost parent (a bit of overkill but it doesn't happen very often anyway); 
	// then, each parent is recompiled completely
	recompile_container parents;
	BOOST_FOREACH(widget *w,recompiles)
	{
		widget *parent = 0,*it = w;
		while (it != 0)
		{
			parent = it;
			it = it->parent_widget();
		}

		SGE_ASSERT(parent != 0);
		parents.insert(parent);
	}

	BOOST_FOREACH(widget *w,parents)
	{
		w->compile();
		render.resize(*w,w->size());
		render.reposition(*w,w->pos());
	}

	mouse.recalculate_focus();
	recompiles.clear();
}

bool sge::gui::detail::update_manager::has_parent(
	widget const &v,
	widget const &w)
{
	if (!v.parent_widget())
		return false;
	
	if (v.parent_widget() == &w)
		return true;
	
	return has_parent(*v.parent_widget(),w);
}
