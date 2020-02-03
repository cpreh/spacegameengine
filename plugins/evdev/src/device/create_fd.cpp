//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/create_fd.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/device/optional_fd_unique_ptr.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/error/strerrno.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::evdev::device::optional_fd_unique_ptr
sge::evdev::device::create_fd(
	fcppt::log::object &_log,
	std::filesystem::path const &_path
)
{
	sge::evdev::device::fd_unique_ptr ret(
		fcppt::make_unique_ptr<
			sge::evdev::device::fd
		>(
			_path
		)
	);

	if(
		ret->valid()
	)
		return
			sge::evdev::device::optional_fd_unique_ptr{
				std::move(
					ret
				)
			};

	// Failure for some evdev files is expected.
	FCPPT_LOG_DEBUG(
		_log,
		fcppt::log::out
			<<
			FCPPT_TEXT("Opening \"")
			<<
			fcppt::filesystem::path_to_string(
				_path
			)
			<<
			FCPPT_TEXT("\" failed: ")
			<<
			fcppt::error::strerrno()
	)

	return
		sge::evdev::device::optional_fd_unique_ptr();
}
