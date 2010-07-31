/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../common.hpp"
#include "../read_pixels.hpp"
#include "../convert/format_to_color.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/bit_depth_bytes.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/image/view/flipped.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/optional_pitch.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

sge::opengl::default_target::default_target(
	dim_type const & _dim,
	renderer::bit_depth::type const _depth
)
:
	buffer_(),
	pos_(
		renderer::pixel_pos::null()
	),
	dim_(_dim),
	stride_(
		renderer::bit_depth_bytes(
			_depth
		)
	)
{}

void
sge::opengl::default_target::pos(
	renderer::pixel_pos const &_pos
)
{
	pos_ = _pos;
}

void
sge::opengl::default_target::dim(
	dim_type const &_dim
)
{
	dim_ = _dim;
}

sge::image::view::const_object const
sge::opengl::target::lock(
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
		_dest.dimension().content()
		* stride_
	);

	bind_me();

	opengl::read_pixels(
		pos_.x() + dest.left(),
		pos_.y() + dest.top(),
		dest.dimension().w(),
		dest.dimension().h(),
		format(),
		format_type(),
		buffer.data()
	);

	return
		image::view::make_const(
			image::view::flipped(
				image::view::make(
					buffer_.data(),
					dim(),
					opengl::convert::format_to_color(
						format(),
						format_type()
					),
					image::view::optional_pitch()
				)
			)
		);
}

void
sge::opengl::target::unlock() const
{
	buffer_.free_memory();
}

sge::renderer::target::dim_type const
sge::opengl::default_target::dim() const
{
	return dim_;
}

// currently 16bit and 32bit framebuffers are supported
// GL_UNSIGNED_BYTE is enough to read 32bit values so take this

GLenum
sge::opengl::default_target::format() const
{
	return GL_RGBA;
}

GLenum
sge::opengl::default_target::format_type() const
{
	return GL_UNSIGNED_BYTE;
}
