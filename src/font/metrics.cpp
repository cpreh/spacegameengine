/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/ascent.hpp>
#include <sge/font/descent.hpp>
#include <sge/font/height.hpp>
#include <sge/font/metrics.hpp>


sge::font::metrics::metrics(
	sge::font::ascent const _ascent,
	sge::font::descent const _descent,
	sge::font::height const _height
)
:
	ascent_(
		_ascent
	),
	descent_(
		_descent
	),
	height_(
		_height
	)
{
}

sge::font::ascent const
sge::font::metrics::ascent() const
{
	return
		ascent_;
}

sge::font::descent const
sge::font::metrics::descent() const
{
	return
		descent_;
}

sge::font::height const
sge::font::metrics::height() const
{
	return
		height_;
}
