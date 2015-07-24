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


#include <sge/opengl/basic_target_impl.hpp>
#include <sge/opengl/onscreen_surface.hpp>
#include <sge/opengl/onscreen_target.hpp>
#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/size.hpp>


sge::opengl::onscreen_target::onscreen_target(
	sge::opengl::context::device::object &_device_context,
	sge::opengl::backend::context &_context,
	awl::window::object &_window
)
:
	base(
		_device_context,
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect::null()
		)
	),
	context_(
		_context
	),
	main_surface_(
		fcppt::unique_ptr_to_base<
			sge::renderer::color_buffer::surface
		>(
			fcppt::make_unique_ptr_fcppt<
				sge::opengl::onscreen_surface
			>(
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

void
sge::opengl::onscreen_target::end_rendering()
{
	context_.end_rendering();
}

sge::renderer::color_buffer::surface const &
sge::opengl::onscreen_target::surface() const
{
	return
		*main_surface_;
}

sge::renderer::screen_unit
sge::opengl::onscreen_target::height() const
{
	return
		fcppt::cast::size<
			sge::renderer::screen_unit
		>(
			main_surface_->size().h()
		);
}

template
class
sge::opengl::basic_target<
	sge::renderer::target::onscreen
>;
