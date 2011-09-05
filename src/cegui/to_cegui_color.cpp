/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cegui/to_cegui_color.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <mizuiro/color/channel/red.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIcolour.h>
#include <fcppt/config/external_end.hpp>

CEGUI::colour const
sge::cegui::to_cegui_color(
	sge::image::color::any::object const &_color
)
{
	sge::image::color::rgba32f const dest(
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_color
		)
	);

	return
		CEGUI::colour(
			dest.get(
				mizuiro::color::channel::red()
			),
			dest.get(
				mizuiro::color::channel::green()
			),
			dest.get(
				mizuiro::color::channel::blue()
			),
			dest.get(
				mizuiro::color::channel::alpha()
			)
		);
}
