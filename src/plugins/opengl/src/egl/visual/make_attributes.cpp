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


#include <sge/opengl/egl/attribute_vector.hpp>
#include <sge/opengl/egl/visual/make_attributes.hpp>
#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/color_bits.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::attribute_vector
sge::opengl::egl::visual::make_attributes(
	sge::renderer::pixel_format::object const &_format
)
{
	sge::opengl::egl::attribute_vector result{
		EGL_BUFFER_SIZE,
		fcppt::cast::to_signed(
			sge::renderer::pixel_format::color_bits(
				_format.color()
			).get()
		)
	};

	auto const push_attribute(
		[
			&result
		](
			EGLint const _attribute,
			EGLint const _value
		)
		{
			result.reserve(
				result.size()
				+
				2
			);

			result.push_back(
				_attribute
			);

			result.push_back(
				_value
			);
		}
	);

	fcppt::maybe_void(
		sge::renderer::pixel_format::depth_bits(
			_format.depth_stencil()
		),
		[
			&push_attribute
		](
			sge::renderer::pixel_format::bit_count const _depth_size
		)
		{
			push_attribute(
				EGL_DEPTH_SIZE,
				fcppt::cast::to_signed(
					_depth_size.get()
				)
			);
		}
	);

	fcppt::maybe_void(
		sge::renderer::pixel_format::stencil_bits(
			_format.depth_stencil()
		),
		[
			&push_attribute
		](
			sge::renderer::pixel_format::bit_count const _stencil_size
		)
		{
			push_attribute(
				EGL_STENCIL_SIZE,
				fcppt::cast::to_signed(
					_stencil_size.get()
				)
			);
		}
	);

	// TODO! Check extensions for srgb support

	result.push_back(
		EGL_NONE
	);

	return
		result;
}
