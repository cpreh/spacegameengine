//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/parameters/convert/bit_depth.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DFORMAT
sge::d3d9::parameters::convert::bit_depth(
	sge::renderer::pixel_format::color const _type
)
{
	switch(
		_type
	)
	{
		// FIXME! This currently doesn't work because the corresponding mizuiro image format is missing!
	//case sge::renderer::pixel_format::color::depth16:
//		break; //return D3DFMT_R5G6B5;
	case sge::renderer::pixel_format::color::depth32:
		return D3DFMT_X8R8G8B8;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
