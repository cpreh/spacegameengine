/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/graph/color_schemes.hpp>
#include <sge/graph/foreground_alt_color.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_from_hex_string.hpp>
#include <sge/image/color/any/object.hpp>


sge::graph::color_scheme const
sge::graph::color_schemes::default_()
{
	return
	sge::graph::color_scheme(
		sge::graph::foreground_color(
			sge::image::color::predef::gray()),
		sge::graph::foreground_alt_color(
			sge::image::color::predef::gray()),
		sge::graph::background_color(
			sge::image::color::predef::black()),
		sge::graph::background_alt_color(
			sge::image::color::predef::black()),
		sge::graph::baseline_color(
			sge::image::color::predef::lightgreen())
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
