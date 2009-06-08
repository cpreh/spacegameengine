/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11/create_window.hpp>
#include <sge/x11/colormap.hpp>
#include <sge/x11/visual.hpp>
#include <sge/x11/display.hpp>
#include <sge/x11/window.hpp>
#include <sge/window/parameters.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/make_shared_ptr.hpp>

sge::window::instance_ptr const
sge::x11::create_window(
	sge::window::parameters const &param,
	display_ptr const dsp,
	int const screen,
	int const depth,
	visual_ptr const visual,
	bool const fullscreen)
{
	x11::colormap_ptr const colormap(
		new x11::colormap(
			dsp,
			screen,
			visual
		)
	);

	if(!param.dim())
		throw exception(
			SGE_TEXT("x11::create_window: Please specify the window's dimensions!")
		);

	return make_shared_ptr<
		sge::x11::window
	>(
		window::pos_type::null(),
		*param.dim(),
		param.title(),
		dsp,
		screen,
		depth,
		fullscreen,
		visual,
		colormap,
		param.class_name()
	);
}
