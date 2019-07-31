//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_INFO_MULTI_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_MULTI_HPP_INCLUDED

#include <sge/x11input/device/info/base.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace info
{

class multi
{
	FCPPT_NONCOPYABLE(
		multi
	);
public:
	explicit
	multi(
		awl::backends::x11::display &
	);

	~multi();

	typedef
	XIDeviceInfo const *
	iterator;

	typedef
	iterator
	const_iterator;

	iterator
	begin() const;

	iterator
	end() const;
private:
	sge::x11input::device::info::base info_base_;
};

}
}
}
}

#endif
