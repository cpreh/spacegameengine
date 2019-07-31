//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/wlinput/cursor/holder.hpp>
#include <awl/backends/wayland/seat.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <fcppt/config/external_end.hpp>


sge::wlinput::cursor::holder::holder(
	awl::backends::wayland::seat const &_seat
)
:
	impl_{
		::wl_seat_get_pointer(
			_seat.get()
		)
	}
{
	FCPPT_ASSERT_ERROR(
		impl_
		!=
		nullptr
	);
}

sge::wlinput::cursor::holder::~holder()
{
	::wl_pointer_release(
		impl_
	);
}

wl_pointer *
sge::wlinput::cursor::holder::get() const
{
	return
		impl_;
}
