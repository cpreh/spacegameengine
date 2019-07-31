//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/com/compare.hpp>
#include <sge/d3d9/com/compare_ptr.hpp>


bool
sge::d3d9::com::compare_ptr(
	IUnknown *const _ptr1,
	IUnknown *const _ptr2
)
{
	return
		_ptr1 == _ptr2
		||
		(
			_ptr1 == nullptr
			||
			_ptr2 == nullptr
			?
				_ptr1
				==
				_ptr2
			:
				sge::d3d9::com::compare(
					*_ptr1,
					*_ptr2
				)
		);
}
