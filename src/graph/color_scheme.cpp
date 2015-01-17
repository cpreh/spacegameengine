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


#include <sge/graph/background_alt_color.hpp>
#include <sge/graph/background_color.hpp>
#include <sge/graph/baseline_color.hpp>
#include <sge/graph/color_scheme.hpp>
#include <sge/graph/foreground_alt_color.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/image/color/any/object.hpp>


sge::graph::color_scheme::color_scheme(
	sge::graph::foreground_color const &_foreground_color,
	sge::graph::foreground_alt_color const &_foreground_alt_color,
	sge::graph::background_color const &_background_color,
	sge::graph::background_alt_color const &_background_alt_color,
	sge::graph::baseline_color const &_baseline_color
)
:
	foreground_color_(
		_foreground_color.get()),
	background_color_(
		_background_color.get()),
	foreground_alt_color_(
		_foreground_alt_color.get()),
	background_alt_color_(
		_background_alt_color.get()),
	baseline_color_(
		_baseline_color.get())
{
}

void
sge::graph::color_scheme::foreground_color(
	sge::image::color::any::object const &_col)
{
	foreground_color_ =
		_col;
}

sge::image::color::any::object const &
sge::graph::color_scheme::foreground_color() const
{
	return foreground_color_;
}

void
sge::graph::color_scheme::background_color(
	sge::image::color::any::object const &_col)
{
	background_color_ =
		_col;
}

sge::image::color::any::object const &
sge::graph::color_scheme::background_color() const
{
	return background_color_;
}

void
sge::graph::color_scheme::foreground_alt_color(
	sge::image::color::any::object const &_col)
{
	foreground_alt_color_ =
		_col;
}

sge::image::color::any::object const &
sge::graph::color_scheme::foreground_alt_color() const
{
	return foreground_alt_color_;
}

void
sge::graph::color_scheme::background_alt_color(
	sge::image::color::any::object const &_col)
{
	background_alt_color_ =
		_col;
}

sge::image::color::any::object const &
sge::graph::color_scheme::background_alt_color() const
{
	return background_alt_color_;
}

void
sge::graph::color_scheme::baseline_color(
	sge::image::color::any::object const &_col)
{
	baseline_color_ =
		_col;
}

sge::image::color::any::object const &
sge::graph::color_scheme::baseline_color() const
{
	return baseline_color_;
}

sge::graph::color_scheme::~color_scheme()
{
}
