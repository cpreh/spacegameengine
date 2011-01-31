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


#include "../default_target.hpp"
#include "../onscreen_surface.hpp"
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::opengl::default_target::default_target(
	sge::window::instance_ptr const _window,
	renderer::bit_depth::type const _depth
)
:
	opengl::target(
		renderer::viewport(
			renderer::pixel_rect(
				renderer::pixel_rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::renderer::pixel_rect::dim
				>(
					_window->size()
				)
			)
		)
	),
	main_surface_(
		fcppt::make_shared_ptr<
			opengl::onscreen_surface
		>(
			_window,
			_depth
		)
	)
{
}

sge::opengl::default_target::~default_target()
{
}

void
sge::opengl::default_target::bind() const
{
}

void
sge::opengl::default_target::unbind() const
{
}

void
sge::opengl::default_target::add_surface(
	renderer::color_surface_ptr
)
{
}

void
sge::opengl::default_target::remove_surface(
	renderer::color_surface_ptr
)
{
}

sge::renderer::color_surface_vector const
sge::opengl::default_target::color_surfaces() const
{
	return
		renderer::color_surface_vector(
			1u,
			main_surface_
		);
}
