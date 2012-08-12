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

