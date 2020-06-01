//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_FD_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_FD_HPP_INCLUDED

#include <sge/evdev/device/fd_fwd.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

class fd
{
	FCPPT_NONMOVABLE(
		fd
	);
public:
	explicit
	fd(
		std::filesystem::path const &
	);

	~fd();

	// FIXME: Return optional_fd here
	[[nodiscard]]
	awl::backends::posix::fd
	get();

	[[nodiscard]]
	bool
	valid() const;
private:
	awl::backends::posix::fd const fd_;
};

}
}
}

#endif
