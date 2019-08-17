//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_OBJECT_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_OBJECT_HPP_INCLUDED

#include <sge/evdev/device/event_fwd.hpp>
#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <awl/backends/posix/fd.hpp>
#include <awl/backends/posix/processor_fwd.hpp>
#include <awl/event/connection_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::evdev::device::fd_unique_ptr &&,
		awl::backends::posix::processor &,
		std::filesystem::path const &
	);

	virtual
	~object();

	awl::event::container
	on_event();

	awl::backends::posix::fd
	posix_fd() const;

	std::filesystem::path const &
	path() const;
protected:
	sge::evdev::device::fd const &
	fd() const;
private:
	virtual
	awl::event::optional_base_unique_ptr
	process_event(
		sge::evdev::device::event const &
	) = 0;

	sge::evdev::device::fd_unique_ptr const fd_;

	awl::event::connection_unique_ptr const fd_connection_;

	std::filesystem::path const path_;
};

}
}
}

#endif
