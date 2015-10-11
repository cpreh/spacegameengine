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


#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_bit_count.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::pixel_format::optional_bit_count
sge::renderer::pixel_format::depth_bits(
	sge::renderer::pixel_format::depth_stencil const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::pixel_format::depth_stencil::off:
		return
			sge::renderer::pixel_format::optional_bit_count();
	case sge::renderer::pixel_format::depth_stencil::d16:
		return
			sge::renderer::pixel_format::optional_bit_count(
				sge::renderer::pixel_format::bit_count(
					16u
				)
			);
	case sge::renderer::pixel_format::depth_stencil::d24:
		return
			sge::renderer::pixel_format::optional_bit_count(
				sge::renderer::pixel_format::bit_count(
					24u
				)
			);
	case sge::renderer::pixel_format::depth_stencil::d32:
		return
			sge::renderer::pixel_format::optional_bit_count(
				sge::renderer::pixel_format::bit_count(
					32u
				)
			);
	case sge::renderer::pixel_format::depth_stencil::d24s8:
		return
			sge::renderer::pixel_format::optional_bit_count(
				sge::renderer::pixel_format::bit_count(
					24u
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
