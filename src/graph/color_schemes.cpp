#include <sge/graph/background_alt_color.hpp>
#include <sge/graph/background_color.hpp>
#include <sge/graph/color_scheme.hpp>
#include <sge/graph/color_schemes.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/graph/foreground_alt_color.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/image/colors.hpp>
#include <sge/graph/baseline_color.hpp>
#include <sge/image/color/rgba8_from_hex_string.hpp>
#include <sge/image/color/any/object.hpp>

sge::graph::color_scheme const
sge::graph::color_schemes::default_()
{
	return
	sge::graph::color_scheme(
		sge::graph::foreground_color(
			sge::image::colors::gray()),
		sge::graph::foreground_alt_color(
			sge::image::colors::gray()),
		sge::graph::background_color(
			sge::image::colors::transparent()),
		sge::graph::background_alt_color(
			sge::image::colors::black()),
		sge::graph::baseline_color(
			sge::image::colors::lightgreen())
	);
}

sge::graph::color_scheme const
sge::graph::color_schemes::bright()
{
	return
	sge::graph::color_scheme(
		sge::graph::foreground_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"F6F792"),
					255))),
		sge::graph::foreground_alt_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"DAEDE2"),
					255))),
		sge::graph::background_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"333745"),
					255))),
		sge::graph::background_alt_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"77C4D3"),
					255))),
		sge::graph::baseline_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"EA2E49"),
					255)))
	);
}

sge::graph::color_scheme const
sge::graph::color_schemes::night()
{
	return
	sge::graph::color_scheme(
		sge::graph::foreground_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"008000"),
					255))),
		sge::graph::foreground_alt_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"77C4D3"),
					255))),
		sge::graph::background_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"2E2E2E"),
					255))),
		sge::graph::background_alt_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"2E2E2E"),
					255))),
		sge::graph::baseline_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"808080"),
					255)))
	);
}

sge::graph::color_scheme const
sge::graph::color_schemes::minimal()
{
	return
	sge::graph::color_scheme(
		sge::graph::foreground_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"808080"),
					255))),
		sge::graph::foreground_alt_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"808080"),
					255))),
		sge::graph::background_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"000000"),
					0))),
		sge::graph::background_alt_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"000000"),
					0))),
		sge::graph::baseline_color(
			sge::image::color::any::object(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"FFFFFF"),
					255)))
	);
}
