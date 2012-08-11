#include <sge/graph/background_alt_color.hpp>
#include <sge/graph/background_color.hpp>
#include <sge/graph/color_scheme.hpp>
#include <sge/graph/color_schemes.hpp>
#include <sge/graph/foreground_alt_color.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/image/colors.hpp>
#include <sge/graph/baseline_color.hpp>

sge::graph::color_scheme const &
sge::graph::color_schemes::default_()
{
	return
	sge::graph::color_scheme(
		sge::graph::foreground_color(
			sge::image::colors::black()),
		sge::graph::foreground_alt_color(
			sge::image::colors::darkblue()),
		sge::graph::background_color(
			sge::image::colors::white()),
		sge::graph::background_alt_color(
			sge::image::colors::lightgray()),
		sge::graph::baseline_color(
			sge::image::colors::yellow())
	);
}
