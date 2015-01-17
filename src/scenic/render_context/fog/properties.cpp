/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/scenic/render_context/fog/properties.hpp>

sge::scenic::render_context::fog::properties::properties(
	sge::scenic::render_context::fog::start const &_start,
	sge::scenic::render_context::fog::end const &_end,
	sge::scenic::render_context::fog::color const &_color)
:
	start_(
		_start),
	end_(
		_end),
	color_(
		_color)
{
}

sge::scenic::render_context::fog::start const &
sge::scenic::render_context::fog::properties::start() const
{
	return
		start_;
}

sge::scenic::render_context::fog::end const &
sge::scenic::render_context::fog::properties::end() const
{
	return
		end_;
}

sge::scenic::render_context::fog::color const &
sge::scenic::render_context::fog::properties::color() const
{
	return
		color_;
}
