//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_bit_count.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::pixel_format::optional_bit_count
sge::renderer::pixel_format::stencil_bits(
	sge::renderer::pixel_format::depth_stencil const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::pixel_format::depth_stencil::off:
	case sge::renderer::pixel_format::depth_stencil::d16:
	case sge::renderer::pixel_format::depth_stencil::d24:
	case sge::renderer::pixel_format::depth_stencil::d32:
		return
			sge::renderer::pixel_format::optional_bit_count();
	case sge::renderer::pixel_format::depth_stencil::d24s8:
		return
			sge::renderer::pixel_format::optional_bit_count(
				sge::renderer::pixel_format::bit_count(
					8u
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
