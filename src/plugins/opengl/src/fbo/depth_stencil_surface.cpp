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


#include <sge/image/ds/format.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/object.hpp>
#include <sge/opengl/convert/depth_stencil_to_internal_format.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/depth_stencil_surface.hpp>
#include <sge/opengl/fbo/render_buffer.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unimplemented_message.hpp>


sge::opengl::fbo::depth_stencil_surface::depth_stencil_surface(
	sge::opengl::fbo::config const &_context,
	sge::renderer::depth_stencil_buffer::surface_parameters const &_parameters
)
:
	sge::renderer::depth_stencil_buffer::surface(),
	render_buffer_(
		_context,
		sge::opengl::convert::depth_stencil_to_internal_format(
			_parameters.format()
		),
		_parameters.size()
	),
	dim_(
		_parameters.size()
	),
	format_(
		_parameters.format()
	)
{
}

sge::opengl::fbo::depth_stencil_surface::~depth_stencil_surface()
{
}

sge::opengl::fbo::render_buffer const &
sge::opengl::fbo::depth_stencil_surface::render_buffer() const
{
	return
		render_buffer_;
}

sge::opengl::fbo::depth_stencil_surface::dim const
sge::opengl::fbo::depth_stencil_surface::size() const
{
	return
		dim_;
}

sge::opengl::fbo::depth_stencil_surface::const_view const
sge::opengl::fbo::depth_stencil_surface::lock(
	lock_area const &_area
) const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("Non texture opengl depth stencil surface currently can't be locked")
	);
}

sge::opengl::fbo::depth_stencil_surface::view const
sge::opengl::fbo::depth_stencil_surface::lock(
	lock_area const &_area,
	sge::renderer::lock_mode const _mode
)
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("Non texture opengl depth stencil surface currently can't be locked")
	);
}

void
sge::opengl::fbo::depth_stencil_surface::unlock() const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("Non texture opengl depth stencil surface currently can't be unlocked")
	);
}

sge::image::ds::format
sge::opengl::fbo::depth_stencil_surface::format() const
{
	return
		format_;
}
