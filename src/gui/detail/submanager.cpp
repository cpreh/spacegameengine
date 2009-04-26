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
#include <sge/gui/detail/submanager.hpp>

sge::gui::detail::submanager::submanager()
{}

void sge::gui::detail::submanager::update() {}
void sge::gui::detail::submanager::add(widgets::base &) {}
void sge::gui::detail::submanager::activation(widgets::base &,activation_state::type) {}
void sge::gui::detail::submanager::remove(widgets::base &) {}
void sge::gui::detail::submanager::dirty(
	widgets::base &,
	rect const &) {}
void sge::gui::detail::submanager::resize(
	widgets::base &,
	dim const &) {}
void sge::gui::detail::submanager::reposition(
	widgets::base &,
	point const &) {}
void sge::gui::detail::submanager::invalidate(
	widgets::base &,
	invalidation::type const &) {}
void sge::gui::detail::submanager::z(
	widgets::base &,
	depth_type) {}
sge::gui::detail::submanager::~submanager() {}
