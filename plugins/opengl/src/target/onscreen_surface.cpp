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


#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/flipped.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/pitch.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/color_to_format.hpp>
#include <sge/opengl/convert/color_to_format_type.hpp>
#include <sge/opengl/target/onscreen_surface.hpp>
#include <sge/opengl/target/read_pixels.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/color_buffer/readable_surface.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/object_impl.hpp>


sge::opengl::target::onscreen_surface::onscreen_surface(
	awl::window::object &_window
)
:
	sge::renderer::color_buffer::readable_surface(),
	window_(
		_window
	),
	buffer_()
{
}

sge::opengl::target::onscreen_surface::~onscreen_surface()
{
}

sge::renderer::color_buffer::readable_surface::const_view
sge::opengl::target::onscreen_surface::lock_c(
	sge::renderer::color_buffer::readable_surface::lock_area const &_dest
) const
{
	if(
		!buffer_.empty()
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("renderer::target()::lock(): already locked!")
			);

	buffer_.resize_uninitialized(
		fcppt::math::dim::contents(
			_dest.size()
		)
		*
		sge::image::color::format_stride(
			this->format()
		)
	);

	sge::opengl::target::read_pixels(
		fcppt::cast::size<
			sge::renderer::pixel_unit
		>(
			fcppt::cast::to_signed(
				_dest.left()
			)
		),
		fcppt::cast::size<
			sge::renderer::pixel_unit
		>(
			fcppt::cast::to_signed(
				_dest.top()
			)
		),
		fcppt::cast::size<
			sge::renderer::screen_unit
		>(
			_dest.size().w()
		),
		fcppt::cast::size<
			sge::renderer::screen_unit
		>(
			_dest.size().h()
		),
		sge::opengl::convert::color_to_format(
			this->format()
		),
		sge::opengl::convert::color_to_format_type(
			this->format()
		),
		buffer_.data()
	);

	return
		sge::image2d::view::flipped(
			sge::image2d::view::make_const(
				buffer_.data(),
				_dest.size(),
				this->format(),
				fcppt::math::dim::null<
					sge::image2d::pitch
				>()
			)
		);
}

void
sge::opengl::target::onscreen_surface::unlock() const
{
	buffer_.free_memory();
}

sge::opengl::target::onscreen_surface::dim
sge::opengl::target::onscreen_surface::size() const
{
	return
		fcppt::math::dim::structure_cast<
			dim,
			fcppt::cast::size_fun
		>(
			window_.size()
		);
}

// Currently, 16bit and 32bit framebuffers are supported. rgba8 is enough to
// read both.

sge::image::color::format
sge::opengl::target::onscreen_surface::format() const
{
	return
		sge::image::color::format::rgba8;
}
