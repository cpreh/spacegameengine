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


#include "../onscreen_target.hpp"
#include "../basic_target_impl.hpp"
#include "../onscreen_surface.hpp"
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::opengl::onscreen_target::onscreen_target(
	sge::window::instance_ptr const _window
)
:
	base(
		renderer::viewport(
			renderer::pixel_rect::null()
		)
	),
	main_surface_(
		fcppt::make_shared_ptr<
			opengl::onscreen_surface
		>(
			_window
		)
	)
{
}

sge::opengl::onscreen_target::~onscreen_target()
{
}

void
sge::opengl::onscreen_target::bind() const
{
}

void
sge::opengl::onscreen_target::unbind() const
{
}


sge::renderer::color_surface_ptr const
sge::opengl::onscreen_target::surface() const
{
	return main_surface_;
}

sge::renderer::screen_unit
sge::opengl::onscreen_target::height() const
{
	return
		static_cast<
			renderer::screen_unit
		>(
			main_surface_->dim().h()
		);
}

template class
sge::opengl::basic_target<
	sge::renderer::onscreen_target
>;
