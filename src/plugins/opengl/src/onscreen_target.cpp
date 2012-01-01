/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/basic_target_impl.hpp>
#include <sge/opengl/onscreen_surface.hpp>
#include <sge/opengl/onscreen_target.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/viewport.hpp>
#include <awl/window/instance_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


sge::opengl::onscreen_target::onscreen_target(
	awl::window::instance &_window
)
:
	base(
		renderer::viewport(
			renderer::pixel_rect::null()
		)
	),
	main_surface_(
		fcppt::make_unique_ptr<
			opengl::onscreen_surface
		>(
			fcppt::ref(
				_window
			)
		)
	)
{
}

sge::opengl::onscreen_target::~onscreen_target()
{
}

void
sge::opengl::onscreen_target::on_bind()
{
}

void
sge::opengl::onscreen_target::on_unbind()
{
}

sge::renderer::color_surface const &
sge::opengl::onscreen_target::surface() const
{
	return *main_surface_;
}

sge::renderer::screen_unit
sge::opengl::onscreen_target::height() const
{
	return
		static_cast<
			renderer::screen_unit
		>(
			main_surface_->size().h()
		);
}

template class
sge::opengl::basic_target<
	sge::renderer::onscreen_target
>;
