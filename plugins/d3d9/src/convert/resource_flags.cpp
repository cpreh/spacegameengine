//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/convert/resource_flags.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <fcppt/container/bitfield/operators.hpp>


sge::d3d9::usage
sge::d3d9::convert::resource_flags(
	sge::renderer::resource_flags_field const &_flags
)
{
	DWORD ret(
		0
	);

	if(
		_flags
		&
		sge::renderer::resource_flags::dynamic
	)
		ret |= D3DUSAGE_DYNAMIC;

	if(
		!(
			_flags
			&
			sge::renderer::resource_flags::readable
		)
	)
		ret |= D3DUSAGE_WRITEONLY;

	return
		sge::d3d9::usage(
			ret
		);
}
