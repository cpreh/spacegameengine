//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/wlinput/focus/scoped_fd.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unistd.h>
#include <fcppt/config/external_end.hpp>


sge::wlinput::focus::scoped_fd::scoped_fd(
	awl::backends::posix::fd const _fd
)
:
	fd_{
		_fd
	}
{
}

sge::wlinput::focus::scoped_fd::~scoped_fd()
{
	::close(
		fd_.get()
	);
}
