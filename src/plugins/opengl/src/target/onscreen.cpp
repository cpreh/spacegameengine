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


#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/target/basic_impl.hpp>
#include <sge/opengl/target/onscreen.hpp>
#include <sge/opengl/target/onscreen_surface.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/color_buffer/readable_surface.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/box/null.hpp>


sge::opengl::target::onscreen::onscreen(
	sge::opengl::context::object &_context,
	sge::opengl::backend::current &_current,
	awl::window::object &_window
)
:
	base(
		_context,
		sge::renderer::target::viewport(
			fcppt::math::box::null<
				sge::renderer::pixel_rect
			>()
		)
	),
	current_(
		_current
	),
	main_surface_(
		fcppt::unique_ptr_to_base<
			sge::renderer::color_buffer::readable_surface
		>(
			fcppt::make_unique_ptr<
				sge::opengl::target::onscreen_surface
			>(
				_window
			)
		)
	)
{
}

sge::opengl::target::onscreen::~onscreen()
{
}

void
sge::opengl::target::onscreen::on_bind()
{
}

void
sge::opengl::target::onscreen::on_unbind()
{
}

void
sge::opengl::target::onscreen::end_rendering()
{
	current_.end_rendering();
}

sge::renderer::color_buffer::readable_surface const &
sge::opengl::target::onscreen::surface() const
{
	return
		*main_surface_;
}

sge::renderer::screen_unit
sge::opengl::target::onscreen::height() const
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
sge::opengl::target::basic<
	sge::renderer::target::onscreen
>;
