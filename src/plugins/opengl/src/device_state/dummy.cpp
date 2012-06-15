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


#include <sge/opengl/create_visual.hpp>
#include <sge/opengl/device_state/context.hpp>
#include <sge/opengl/device_state/create_context.hpp>
#include <sge/opengl/device_state/dummy.hpp>
#include <sge/opengl/glew/initialize.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/windowed.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/window/object.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/text.hpp>


sge::opengl::device_state::dummy::dummy()
:
	awl_system_(
		awl::system::create()
	),
	awl_visual_(
		// TODO: This is a hack for Windows, but is it wise? What if this visual isn't supported?
		sge::opengl::create_visual(
			*awl_system_,
			sge::renderer::parameters(
				sge::renderer::screen_mode(
					sge::renderer::windowed(
						sge::renderer::bit_depth::depth32
					)
				),
				sge::renderer::depth_stencil_buffer::off,
				sge::renderer::vsync::off,
				sge::renderer::no_multi_sampling
			)
		)
	),
	awl_window_(
		awl_system_->create_window(
			awl::window::parameters(
				*awl_visual_
			)
			// FIXME: Make it possible to omit this
			.size(
				awl::window::dim(
					100,
					100
				)
			)
			.class_name(
				FCPPT_TEXT("sgeopengl_dummy_window")
			)
		)
	),
	context_(
		sge::opengl::device_state::create_context(
			*awl_window_
		)
	),
	scoped_current_(
		*context_
	)
{
	sge::opengl::glew::initialize();
}

sge::opengl::device_state::dummy::~dummy()
{
}
