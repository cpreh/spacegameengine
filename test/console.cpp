/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/window/parameters.hpp>
#include <sge/console/console.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <ostream>
#include <cstdlib>

void func(
	sge::con::arg_list const &)
{
}

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge console test")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					1024,
					768),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::image));
	
	sge::con::add(
		SGE_TEXT("test"),
		func);
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
