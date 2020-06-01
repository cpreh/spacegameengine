//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/fd.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sge::evdev::device::fd::fd(
	std::filesystem::path const &_path
)
:
	fd_(
		::open( // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
			_path.string().c_str(),
			O_RDONLY | O_NONBLOCK | O_CLOEXEC // NOLINT(hicpp-signed-bitwise)
		)
	)
{
}

sge::evdev::device::fd::~fd()
{
	if(
		this->valid()
	)
	{
		::close(
			fd_.get()
		);
	}
}

awl::backends::posix::fd
sge::evdev::device::fd::get()
{
	FCPPT_ASSERT_PRE(
		this->valid()
	);

	return
		fd_;
}

bool
sge::evdev::device::fd::valid() const
{
	return
		this->fd_.get()
		!=
		-1;
}
