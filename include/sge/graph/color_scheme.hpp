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


#ifndef SGE_GRAPH_COLOR_SCHEME_HPP_INCLUDED
#define SGE_GRAPH_COLOR_SCHEME_HPP_INCLUDED

#include <sge/graph/background_alt_color.hpp>
#include <sge/graph/background_color.hpp>
#include <sge/graph/baseline_color.hpp>
#include <sge/graph/foreground_alt_color.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/graph/symbol.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace graph
{

class color_scheme
{
public:
	SGE_GRAPH_SYMBOL
	color_scheme(
		sge::graph::foreground_color const &,
		sge::graph::foreground_alt_color const &,
		sge::graph::background_color const &,
		sge::graph::background_alt_color const &,
		sge::graph::baseline_color const &);

	SGE_GRAPH_SYMBOL
	void
	foreground_color(
		sge::image::color::any::object const &);

	SGE_GRAPH_SYMBOL
	sge::image::color::any::object const &
	foreground_color() const;

	SGE_GRAPH_SYMBOL
	void
	background_color(
		sge::image::color::any::object const &);

	SGE_GRAPH_SYMBOL
	sge::image::color::any::object const &
	background_color() const;

	SGE_GRAPH_SYMBOL
	void
	foreground_alt_color(
		sge::image::color::any::object const &);

	SGE_GRAPH_SYMBOL
	sge::image::color::any::object const &
	foreground_alt_color() const;

	SGE_GRAPH_SYMBOL
	void
	background_alt_color(
		sge::image::color::any::object const &);

	SGE_GRAPH_SYMBOL
	sge::image::color::any::object const &
	background_alt_color() const;

	SGE_GRAPH_SYMBOL
	void
	baseline_color(
		sge::image::color::any::object const &);

	SGE_GRAPH_SYMBOL
	sge::image::color::any::object const &
	baseline_color() const;

	SGE_GRAPH_SYMBOL
	~color_scheme();

private:
	sge::image::color::any::object
	foreground_color_;

	sge::image::color::any::object
	background_color_;

	sge::image::color::any::object
	foreground_alt_color_;

	sge::image::color::any::object
	background_alt_color_;

	sge::image::color::any::object
	baseline_color_;
};

}
}

#endif

