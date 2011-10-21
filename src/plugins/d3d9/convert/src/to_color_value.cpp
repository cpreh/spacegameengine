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


#include "../to_color_value.hpp"
#include "../../d3dinclude.hpp"
#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>


D3DCOLORVALUE const
sge::d3d9::convert::to_color_value(
	sge::image::color::any::object const &_color
)
{
	sge::image::color::rgba32f const conv(
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_color
		)
	);

	D3DCOLORVALUE const ret =
	{
		conv.get(
			mizuiro::color::channel::red()
		),
		conv.get(
			mizuiro::color::channel::green()
		),
		conv.get(
			mizuiro::color::channel::blue()
		),
		conv.get(
			mizuiro::color::channel::alpha()
		)
	};

	return ret;
}
