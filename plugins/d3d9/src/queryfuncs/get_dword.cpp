//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/queryfuncs/get_data.hpp>
#include <sge/d3d9/queryfuncs/get_dword.hpp>
#include <sge/d3d9/queryfuncs/optional_dword.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size.hpp>


sge::d3d9::queryfuncs::optional_dword const
sge::d3d9::queryfuncs::get_dword(
	IDirect3DQuery9 &_query,
	DWORD const _flags
)
{
	DWORD result;

	DWORD const size(
		fcppt::cast::size<
			DWORD
		>(
			sizeof(
				DWORD
			)
		)
	);

	FCPPT_ASSERT_PRE(
		_query.GetDataSize()
		==
		size
	);

	return
		sge::d3d9::queryfuncs::get_data(
			_query,
			&result,
			size,
			_flags
		)
		?
			sge::d3d9::queryfuncs::optional_dword(
				result
			)
		:
			sge::d3d9::queryfuncs::optional_dword()
		;
}
