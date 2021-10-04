//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
			{};
	case sge::renderer::pixel_format::depth_stencil::d16:
		return
			sge::renderer::pixel_format::optional_bit_count(
				sge::renderer::pixel_format::bit_count(
					16U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				)
			);
	case sge::renderer::pixel_format::depth_stencil::d24:
		return
			sge::renderer::pixel_format::optional_bit_count(
				sge::renderer::pixel_format::bit_count(
					24U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				)
			);
	case sge::renderer::pixel_format::depth_stencil::d32:
		return
			sge::renderer::pixel_format::optional_bit_count(
				sge::renderer::pixel_format::bit_count(
					32U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				)
			);
	case sge::renderer::pixel_format::depth_stencil::d24s8:
		return
			sge::renderer::pixel_format::optional_bit_count(
				sge::renderer::pixel_format::bit_count(
					24U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
