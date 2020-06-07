//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/graph/background_alt_color.hpp>
#include <sge/graph/background_color.hpp>
#include <sge/graph/baseline_color.hpp>
#include <sge/graph/color_scheme.hpp>
#include <sge/graph/color_schemes.hpp>
#include <sge/graph/foreground_alt_color.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_from_hex_string.hpp>


namespace
{

constexpr
sge::image::color::rgba8::format::channel_type const full_alpha{
	255
};

}

sge::graph::color_scheme
sge::graph::color_schemes::default_()
{
	return
		sge::graph::color_scheme(
			sge::graph::foreground_color(
				sge::image::color::predef::gray()
			),
			sge::graph::foreground_alt_color(
				sge::image::color::predef::gray()
			),
			sge::graph::background_color(
				sge::image::color::predef::black()
			),
			sge::graph::background_alt_color(
				sge::image::color::predef::black()
			),
			sge::graph::baseline_color(
				sge::image::color::predef::lightgreen()
			)
		);
}

sge::graph::color_scheme
sge::graph::color_schemes::bright()
{
	return
		sge::graph::color_scheme(
			sge::graph::foreground_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"F6F792"
					),
					full_alpha
				)
			),
			sge::graph::foreground_alt_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"DAEDE2"
					),
					full_alpha
				)
			),
			sge::graph::background_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"333745"
					),
					full_alpha
				)
			),
			sge::graph::background_alt_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"77C4D3"
					),
					full_alpha
				)
			),
			sge::graph::baseline_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"EA2E49"
					),
					full_alpha
				)
			)
		);
}

sge::graph::color_scheme
sge::graph::color_schemes::night()
{
	return
		sge::graph::color_scheme(
			sge::graph::foreground_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"008000"
					),
					full_alpha
				)
			),
			sge::graph::foreground_alt_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"77C4D3"
					),
					full_alpha
				)
			),
			sge::graph::background_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"2E2E2E"
					),
					full_alpha
				)
			),
			sge::graph::background_alt_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"2E2E2E"
					),
					full_alpha
				)
			),
			sge::graph::baseline_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"808080"
					),
					full_alpha
				)
			)
		);
}

sge::graph::color_scheme
sge::graph::color_schemes::minimal()
{
	return
		sge::graph::color_scheme(
			sge::graph::foreground_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"808080"
					),
					full_alpha
				)
			),
			sge::graph::foreground_alt_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"808080"
					),
					full_alpha
				)
			),
			sge::graph::background_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"000000"
					),
					0
				)
			),
			sge::graph::background_alt_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"000000"
					),
					0
				)
			),
			sge::graph::baseline_color(
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"FFFFFF"
					),
					full_alpha
				)
			)
		);
}
