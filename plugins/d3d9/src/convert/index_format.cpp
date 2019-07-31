//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/index_format.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DFORMAT
sge::d3d9::convert::index_format(
	sge::renderer::index::dynamic::format const _format
)
{
	switch(
		_format
	)
	{
	case sge::renderer::index::dynamic::format::i16:
		return
			D3DFMT_INDEX16;
	case sge::renderer::index::dynamic::format::i32:
		return
			D3DFMT_INDEX32;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
