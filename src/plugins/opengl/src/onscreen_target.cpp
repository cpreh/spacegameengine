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
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/fbo/bind.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/opengl/fbo/no_buffer.hpp>
#include <sge/opengl/fbo/unbind.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/viewport.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>


sge::opengl::onscreen_target::onscreen_target(
	sge::opengl::context::object &_context,
	awl::window::object &_window
)
:
	base(
		renderer::viewport(
			renderer::pixel_rect::null()
		)
	),
	context_(
		_context
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
sge::opengl::onscreen_target::clear(
	sge::renderer::clear::parameters const &_parameters
)
{
	sge::opengl::fbo::context &fbo_context(
		sge::opengl::context::use<
			sge::opengl::fbo::context
		>(
			context_
		)
	);

	sge::opengl::fbo::id const last_id(
		fbo_context.last_buffer()
	);

	if(
		last_id
		!=
		sge::opengl::fbo::no_buffer()
	)
		sge::opengl::fbo::unbind(
			fbo_context
		);

	base::clear(
		_parameters
	);

	if(
		last_id
		!=
		sge::opengl::fbo::no_buffer()
	)
		sge::opengl::fbo::bind(
			fbo_context,
			last_id
		);
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
