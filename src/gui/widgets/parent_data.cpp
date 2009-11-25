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


#include <sge/gui/widgets/base.hpp>
#include <sge/gui/widgets/parent_data.hpp>

sge::gui::widgets::parent_data::parent_data(
	base &wref)
:
	widget_(&wref),
	manager_(wref.parent_manager())
{
}

sge::gui::widgets::parent_data::parent_data(
	manager &manager_)
:
	widget_(0),
	manager_(manager_)
{
}

sge::gui::widgets::base *sge::gui::widgets::parent_data::parent_widget() const
{
	return widget_;
}

sge::gui::manager &sge::gui::widgets::parent_data::parent_manager() const
{
	return manager_;
}
