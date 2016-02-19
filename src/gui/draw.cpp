/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/gui/draw.hpp>
#include <sge/gui/background/base.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


void
sge::gui::draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::gui::background::base &_background,
	sge::gui::main_area::base &_main_area
)
{
	_background.draw(
		_renderer,
		_context
	);

	_main_area.widget().on_draw(
		_renderer,
		_context
	);
}
