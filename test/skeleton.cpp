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



#include <sge/mainloop/skeleton.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/key_type.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/window/parameters.hpp>
#include <sge/systems/list.hpp>
#include <sge/text.hpp>

namespace
{

struct app : public sge::mainloop::skeleton {
	app();
private:
	void loop();
	void key_event(
		sge::input::key_pair const &);
};

}

int main()
try
{
	app a;
	a.run();
}
SGE_MAINLOOP_CATCH_BLOCK

app::app()
:
	sge::mainloop::skeleton(
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("sge skeletontest")
			)
		)
		(
			sge::renderer::parameters(
				sge::renderer::display_mode(
					sge::renderer::screen_size(
						1024,
						768
					),
					sge::renderer::bit_depth::depth32,
					sge::renderer::refresh_rate_dont_care
				),
				sge::renderer::depth_buffer::off,
				sge::renderer::stencil_buffer::off,
				sge::renderer::window_mode::windowed,
				sge::renderer::vsync::on,
				sge::renderer::no_multi_sampling
			)
		)
		(sge::systems::parameterless::input))
{
	system().renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
	);
}

namespace
{

void app::loop()
{
	sge::renderer::scoped_block const block(
		system().renderer()
	);
}

void app::key_event(
	sge::input::key_pair const &e)
{
	if(e.key().code() == sge::input::kc::key_escape)
		exit();
}

}
