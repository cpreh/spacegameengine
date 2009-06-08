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


#include <sge/gui/size_policy.hpp>

sge::gui::size_policy const sge::gui::size_policy::default_policy(
	axis_policy::type(axis_policy::can_grow) | axis_policy::can_shrink,
	axis_policy::type(axis_policy::can_grow) | axis_policy::can_shrink);

sge::gui::size_policy::size_policy(
	axis_policy::type const &x_,
	axis_policy::type const &y_)
	: x_(x_),
	  y_(y_) 
{}

sge::gui::axis_policy::type const &sge::gui::size_policy::x() const 
{ 
	return x_; 
}

sge::gui::axis_policy::type const &sge::gui::size_policy::y() const 
{ 
	return y_; 
}

// this is a hack so we can use it with the layouts::row::master stuff
sge::gui::axis_policy::type const &sge::gui::size_policy::index(
	std::size_t const i) const
{ 
	return i == static_cast<std::size_t>(0) ? x() : y(); 
}
