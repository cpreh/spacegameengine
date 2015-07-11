/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/gui/background/base.hpp>
#include <sge/gui/background/colored.hpp>
#include <sge/gui/impl/fill_rect.hpp>
#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>


sge::gui::background::colored::colored(
	sge::gui::main_area::base &_main_area
)
:
	sge::gui::background::base(
		_main_area
	)
{
}

sge::gui::background::colored::~colored()
{
}

void
sge::gui::background::colored::on_draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
)
{
	_renderer.fill_rect(
		_context,
		_area,
		sge::image::color::any::object(
			sge::image::color::rgba8(
				(sge::image::color::init::red() %= .75)
				(sge::image::color::init::green() %= .75)
				(sge::image::color::init::blue() %= .75)
				(sge::image::color::init::alpha() %= .25)
			)
		)
	);
}
