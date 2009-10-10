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


#include <sge/gui/layouts/base.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/exception.hpp>
#include <sge/gui/log.hpp>
#include <sge/type_name.hpp>
#include <sge/text.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("layouts: base"),
	false);
}

sge::gui::layouts::base::base()
:
	w(0)
{
}

void sge::gui::layouts::base::compile(invalidation::type const &i)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("in compile of widget: ")
		        << type_name(typeid(connected_widget())));

	if (i & invalidation::position)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_ << SGE_TEXT("position invalid"));

		// Currently, the layout doesn't support any internal size hints (just the
		// global one which sets the widget's position
		if (!connected_widget().has_parent())
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_ << SGE_TEXT("setting raw new position"));

			base::set_widget_pos(
				connected_widget(),
				connected_widget().pos_hint() 
					? *connected_widget().pos_hint()
					: point::null());
		}
	}

	if (!(i & invalidation::size))
		return;
		
	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("size invalid, so recompiling"));
	
	dim const s = 
		connected_widget().optimal_size();

	// Widget hasn't been resized yet?
	if (connected_widget().size() != s)
		base::set_widget_size(
			connected_widget(),
			s);

	compile_static();
}

void sge::gui::layouts::base::invalidate(
	widgets::base&,
	invalidation::type const &t)
{
	if (connected_widget().has_parent())
		connected_widget().parent_widget().invalidate(
			connected_widget(),
			t);
	else
		connected_widget().parent_manager().invalidate(
			connected_widget(),
			t);
}

sge::gui::widgets::base&
sge::gui::layouts::base::connected_widget()
{
	return *w;
}

sge::gui::widgets::base const &
sge::gui::layouts::base::connected_widget() const
{
	return *w;
}

sge::gui::layouts::base::~base()
{}

void sge::gui::layouts::base::set_widget_size(
	widgets::base &w,
	dim const &d)
{
	w.size(d);
}

void sge::gui::layouts::base::set_widget_pos(
	widgets::base &w,
	point const &d)
{
	w.pos(d);
}

void sge::gui::layouts::base::compile_widget(
	widgets::base &w,
	invalidation::type const &)
{
	w.compile_static();
}

void sge::gui::layouts::base::connected_widget(widgets::base &_w)
{
	if (w)
		throw exception(SGE_TEXT("registered connected widgets::base twice"));
	
	w = &_w;
}
