//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/bool.hpp>
#include <sge/d3d9/state/convert/bool_to_dword.hpp>


DWORD
sge::d3d9::state::convert::bool_to_dword(
	bool const _value
)
{
	return
		static_cast<
			DWORD
		>(
			sge::d3d9::convert::bool_(
				_value
			)
		);
}
