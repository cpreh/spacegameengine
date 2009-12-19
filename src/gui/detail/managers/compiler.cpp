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


#include <sge/gui/detail/managers/compiler.hpp>
#include <sge/gui/detail/managers/render.hpp>
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/log.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <sge/log/headers.hpp>
#include <sge/assert.hpp>
#include <sge/type_info.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

namespace
{

sge::log::object mylogger(
	sge::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("managers: compiler")
	)
);

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
	SGE_LOG_DEBUG(
		mylogger,
		log::_
			<< FCPPT_TEXT("adding widget ")
			<< type_info(typeid(w)).name()
			<< FCPPT_TEXT(" to invalidate list"));

	// since we cannot assume that widgets::base is fully constructed (just the base
	// class: widget), we defer invalidation to a later point of time
	insert_or_combine(
		invalidates,
		w,
		invalidation::all);
}

void sge::gui::detail::managers::compiler::remove(widgets::base &w)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_
			<< FCPPT_TEXT("deleting a widget of type ")
			<< type_info(typeid(w)).name());

	// remove now dead references from recompile list
	for (recompile_container::iterator it = recompiles.begin(),next = it;
		   it != recompiles.end();
		   it = next)
	{
		++next;

		if (it->first == &w || has_parent(*(it->first),w))
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
			log::_ << FCPPT_TEXT("inserting parent to invalidates list"));
		invalidates.insert(
			std::make_pair(
				&(w.parent_widget()),
				invalidation::all));
	}
}

void sge::gui::detail::managers::compiler::update()
{
	if (recompiles.empty() && invalidates.empty())
	{
		/*
		SGE_LOG_DEBUG(
			mylogger,
			log::_ << FCPPT_TEXT("in update, but nothing to do!"));
			*/
		return;
	}

	// the parents of invalidates widgets can now be safely invalidated
	BOOST_FOREACH(recompile_container::const_reference r,invalidates)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_
				<< FCPPT_TEXT("invalidating widget's parent: ")
				<< type_info(typeid(r.first)).name());
		r.first->invalidate(
			*r.first,
			r.second);
	}
	invalidates.clear();

	BOOST_FOREACH(recompile_container::const_reference r,recompiles)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_
				<< FCPPT_TEXT("compiling widget of type ")
				<< type_info(typeid(*r.first)).name());
		r.first->compile(
			r.second);
	}
	recompiles.clear();

	mouse_.recalculate_focus();
}

void sge::gui::detail::managers::compiler::invalidate(
	widgets::base &w,
	invalidation::type const &i)
{
	insert_or_combine(
		recompiles,
		w,
		i);
}

void sge::gui::detail::managers::compiler::insert_or_combine(
	recompile_container &c,
	widgets::base &w,
	invalidation::type const &i)
{
	recompile_container::iterator it =
		c.find(&w);

	if (it != c.end())
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_ << FCPPT_TEXT("widget already in list, combining"));
		it->second |= i;
	}
	else
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_ << FCPPT_TEXT("inserting widget"));
		c.insert(
			std::make_pair(
				&w,i));
	}
}
