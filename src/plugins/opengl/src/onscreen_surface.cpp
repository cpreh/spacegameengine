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


#include "../onscreen_surface.hpp"
#include "../common.hpp"
#include "../read_pixels.hpp"
#include "../convert/format_to_color.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/flipped.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

sge::opengl::onscreen_surface::onscreen_surface(
	sge::window::instance &_window
)
:
	sge::renderer::color_surface(),
	window_(_window),
	buffer_(),
	stride_(
		4u
	)
{
}

sge::opengl::onscreen_surface::~onscreen_surface()
{
}

sge::opengl::onscreen_surface::const_view const
sge::opengl::onscreen_surface::lock(
	renderer::lock_rect const &_dest
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

	opengl::read_pixels(
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
		this->format(),
		this->format_type(),
		buffer_.data()
	);

	return
		image2d::view::flipped(
			image2d::view::make_const(
				buffer_.data(),
				_dest.size(),
				opengl::convert::format_to_color(
					this->format(),
					this->format_type()
				),
				image2d::view::optional_pitch()
			)
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

// currently 16bit and 32bit framebuffers are supported
// GL_UNSIGNED_BYTE is enough to read 32bit values so take this

sge::opengl::color_format const
sge::opengl::onscreen_surface::format() const
{
	return
		opengl::color_format(
			GL_RGBA
		);
}

sge::opengl::color_format_type const
sge::opengl::onscreen_surface::format_type() const
{
	return
		opengl::color_format_type(
			GL_UNSIGNED_BYTE
		);
}
