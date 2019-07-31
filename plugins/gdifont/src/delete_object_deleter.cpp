//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gdifont/delete_object_deleter.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/assert/error.hpp>


void
sge::gdifont::delete_object_deleter::operator()(
	HGDIOBJ const _object
) const
{
	if(
		_object
		!=
		nullptr
	)
		FCPPT_ASSERT_ERROR(
			::DeleteObject(
				_object
			)
			!= 0
		);
}
