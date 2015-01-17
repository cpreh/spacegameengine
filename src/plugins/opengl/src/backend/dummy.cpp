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


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/dummy.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/glew/initialize.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <awl/system/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/window/object.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/text.hpp>


sge::opengl::backend::dummy::dummy(
	awl::system::object &_awl_system,
	sge::opengl::backend::system &_device_system
)
:
	awl_visual_(
		// TODO: This is a hack for querying device caps, but is it
		// wise? What if this visual isn't supported?
		_device_system.create_visual(
			sge::renderer::pixel_format::object(
				sge::renderer::pixel_format::color::depth32,
				sge::renderer::pixel_format::depth_stencil::off,
				sge::renderer::pixel_format::optional_multi_samples(),
				sge::renderer::pixel_format::srgb::no
			)
		)
	),
	awl_window_(
		_awl_system.create_window(
			awl::window::parameters(
				*awl_visual_
			)
			.class_name(
				FCPPT_TEXT("sgeopengl_dummy_window")
			)
		)
	),
	context_(
		_device_system.create_context(
			*awl_window_
		)
	),
	scoped_current_(
		*context_
	)
{
	sge::opengl::glew::initialize();
}

sge::opengl::backend::dummy::~dummy()
{
}
