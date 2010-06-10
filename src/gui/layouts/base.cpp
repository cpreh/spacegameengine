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
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/text.hpp>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("layouts_base")
	)
);

}

sge::gui::layouts::base::base()
:
	w(0)
{
}

void sge::gui::layouts::base::compile(invalidation::type const &i)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("in compile of widget: ")
			<< fcppt::type_name(typeid(connected_widget()))
	);

	if (i & invalidation::position)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("position invalid"));

		// Currently, the layout doesn't support any internal size hints (just the
		// global one which sets the widget's position
		if (!connected_widget().has_parent())
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ << FCPPT_TEXT("setting raw new position"));

			base::set_widget_pos(
				connected_widget(),
				connected_widget().pos_hint()
					? *connected_widget().pos_hint()
					: point::null());
		}
	}

	if (!(i & invalidation::size))
		return;

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("size invalid, so recompiling"));

	dim const s =
		connected_widget().optimal_size();

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("optimal size is ") << s);

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
		throw exception(FCPPT_TEXT("registered connected widgets::base twice"));

	w = &_w;
}
