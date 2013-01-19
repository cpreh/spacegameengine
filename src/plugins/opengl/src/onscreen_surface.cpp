/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/format.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/flipped.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/pitch.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/onscreen_surface.hpp>
#include <sge/opengl/read_pixels.hpp>
#include <sge/opengl/convert/color_to_format.hpp>
#include <sge/opengl/convert/color_to_format_type.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <awl/window/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/object_impl.hpp>


sge::opengl::onscreen_surface::onscreen_surface(
	awl::window::object &_window
)
:
	sge::renderer::color_buffer::surface(),
	window_(
		_window
	),
	buffer_(),
	stride_(
		4u
	)
{
}

sge::opengl::onscreen_surface::~onscreen_surface()
{
}

sge::renderer::color_buffer::surface::const_view const
sge::opengl::onscreen_surface::lock(
	sge::renderer::color_buffer::surface::lock_area const &_dest
) const
{
	if(
		!buffer_.empty()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("renderer::target()::lock(): already locked!")
		);

	buffer_.resize_uninitialized(
		_dest.size().content()
		* stride_
	);

	sge::opengl::read_pixels(
		static_cast<
			renderer::pixel_unit
		>(
			_dest.left()
		),
		static_cast<
			renderer::pixel_unit
		>(
			_dest.top()
		),
		_dest.size().w(),
		_dest.size().h(),
		this->color_format(),
		this->color_format_type(),
		buffer_.data()
	);

	return
		sge::image2d::view::flipped(
			sge::image2d::view::make_const(
				buffer_.data(),
				_dest.size(),
				this->format(),
				sge::image2d::pitch::null()
			)
		);
}

sge::renderer::color_buffer::surface::view const
sge::opengl::onscreen_surface::lock(
	sge::renderer::color_buffer::surface::lock_area const &,
	sge::renderer::lock_mode
)
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("Locking onscreen surfaces for writing is not implemented")
	);
}

void
sge::opengl::onscreen_surface::unlock() const
{
	buffer_.free_memory();
}

sge::opengl::onscreen_surface::dim const
sge::opengl::onscreen_surface::size() const
{
	return
		fcppt::math::dim::structure_cast<
			dim
		>(
			window_.size()
		);
}

// Currently, 16bit and 32bit framebuffers are supported. rgba8 is enough to
// read both.

sge::image::color::format
sge::opengl::onscreen_surface::format() const
{
	return
		sge::image::color::format::rgba8;
}

sge::opengl::color_format const
sge::opengl::onscreen_surface::color_format() const
{
	return
		sge::opengl::convert::color_to_format(
			this->format()
		);
}

sge::opengl::color_format_type const
sge::opengl::onscreen_surface::color_format_type() const
{
	return
		sge::opengl::convert::color_to_format_type(
			this->format()
		);
}
