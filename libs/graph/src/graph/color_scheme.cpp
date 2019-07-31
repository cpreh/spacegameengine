//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/graph/background_alt_color.hpp>
#include <sge/graph/background_color.hpp>
#include <sge/graph/baseline_color.hpp>
#include <sge/graph/color.hpp>
#include <sge/graph/color_scheme.hpp>
#include <sge/graph/foreground_alt_color.hpp>
#include <sge/graph/foreground_color.hpp>


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
	sge::graph::color const &_col)
{
	foreground_color_ =
		_col;
}

sge::graph::color const &
sge::graph::color_scheme::foreground_color() const
{
	return foreground_color_;
}

void
sge::graph::color_scheme::background_color(
	sge::graph::color const &_col)
{
	background_color_ =
		_col;
}

sge::graph::color const &
sge::graph::color_scheme::background_color() const
{
	return background_color_;
}

void
sge::graph::color_scheme::foreground_alt_color(
	sge::graph::color const &_col)
{
	foreground_alt_color_ =
		_col;
}

sge::graph::color const &
sge::graph::color_scheme::foreground_alt_color() const
{
	return foreground_alt_color_;
}

void
sge::graph::color_scheme::background_alt_color(
	sge::graph::color const &_col)
{
	background_alt_color_ =
		_col;
}

sge::graph::color const &
sge::graph::color_scheme::background_alt_color() const
{
	return background_alt_color_;
}

void
sge::graph::color_scheme::baseline_color(
	sge::graph::color const &_col)
{
	baseline_color_ =
		_col;
}

sge::graph::color const &
sge::graph::color_scheme::baseline_color() const
{
	return baseline_color_;
}
