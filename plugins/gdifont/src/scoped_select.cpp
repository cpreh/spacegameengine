//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/scoped_select.hpp>
#include <sge/gdifont/select_object.hpp>


sge::gdifont::scoped_select::scoped_select(
	sge::gdifont::device_context const &_device_context,
	HGDIOBJ const _object
)
:
	device_context_(
		_device_context
	),
	previous_(
		sge::gdifont::select_object(
			device_context_,
			_object
		)
	)
{
}

sge::gdifont::scoped_select::~scoped_select()
{
	sge::gdifont::select_object(
		device_context_,
		previous_
	);
}
