//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GRAPH_COLOR_SCHEME_HPP_INCLUDED
#define SGE_GRAPH_COLOR_SCHEME_HPP_INCLUDED

#include <sge/graph/background_alt_color.hpp>
#include <sge/graph/background_color.hpp>
#include <sge/graph/baseline_color.hpp>
#include <sge/graph/color.hpp>
#include <sge/graph/foreground_alt_color.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/graph/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace graph
{

class color_scheme
{
public:
	SGE_GRAPH_DETAIL_SYMBOL
	color_scheme(
		sge::graph::foreground_color const &,
		sge::graph::foreground_alt_color const &,
		sge::graph::background_color const &,
		sge::graph::background_alt_color const &,
		sge::graph::baseline_color const &);

	SGE_GRAPH_DETAIL_SYMBOL
	void
	foreground_color(
		sge::graph::color const &);

	SGE_GRAPH_DETAIL_SYMBOL
	sge::graph::color const &
	foreground_color() const;

	SGE_GRAPH_DETAIL_SYMBOL
	void
	background_color(
		sge::graph::color const &);

	SGE_GRAPH_DETAIL_SYMBOL
	sge::graph::color const &
	background_color() const;

	SGE_GRAPH_DETAIL_SYMBOL
	void
	foreground_alt_color(
		sge::graph::color const &);

	SGE_GRAPH_DETAIL_SYMBOL
	sge::graph::color const &
	foreground_alt_color() const;

	SGE_GRAPH_DETAIL_SYMBOL
	void
	background_alt_color(
		sge::graph::color const &);

	SGE_GRAPH_DETAIL_SYMBOL
	sge::graph::color const &
	background_alt_color() const;

	SGE_GRAPH_DETAIL_SYMBOL
	void
	baseline_color(
		sge::graph::color const &);

	SGE_GRAPH_DETAIL_SYMBOL
	sge::graph::color const &
	baseline_color() const;
private:
	sge::graph::color
	foreground_color_;

	sge::graph::color
	background_color_;

	sge::graph::color
	foreground_alt_color_;

	sge::graph::color
	background_alt_color_;

	sge::graph::color
	baseline_color_;
};

}
}

#endif

