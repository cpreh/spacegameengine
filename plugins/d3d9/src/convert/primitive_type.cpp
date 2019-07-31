//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/primitive_type.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DPRIMITIVETYPE
sge::d3d9::convert::primitive_type(
	sge::renderer::primitive_type const _primitive_type
)
{
	switch(
		_primitive_type
	)
	{
	case sge::renderer::primitive_type::point_list:
		return
			D3DPT_POINTLIST;
	case sge::renderer::primitive_type::line_list:
		return
			D3DPT_LINELIST;
	case sge::renderer::primitive_type::triangle_list:
		return
			D3DPT_TRIANGLELIST;
	case sge::renderer::primitive_type::line_strip:
		return
			D3DPT_LINESTRIP;
	case sge::renderer::primitive_type::triangle_strip:
		return
			D3DPT_TRIANGLESTRIP;
	case sge::renderer::primitive_type::triangle_fan:
		return
			D3DPT_TRIANGLEFAN;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
