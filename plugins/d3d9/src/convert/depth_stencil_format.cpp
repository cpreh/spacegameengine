//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/depth_stencil_format.hpp>
#include <sge/image/ds/format.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DFORMAT
sge::d3d9::convert::depth_stencil_format(
	sge::image::ds::format const _format
)
{
	switch(
		_format
	)
	{
	case sge::image::ds::format::d16:
		return
			D3DFMT_D16;
	case sge::image::ds::format::d24s8:
		return
			D3DFMT_D24S8;
	case sge::image::ds::format::d32:
		return
			D3DFMT_D32;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
