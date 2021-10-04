//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_INFO_MULTI_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_MULTI_HPP_INCLUDED

#include <sge/x11input/device/info/base.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge::x11input::device::info
{

class multi
{
	FCPPT_NONMOVABLE(
		multi
	);
public:
	explicit
	multi(
		awl::backends::x11::display_ref
	);

	~multi();

	using
	iterator
	=
	XIDeviceInfo const *;

	using
	const_iterator
	=
	iterator;

	[[nodiscard]]
	iterator
	begin() const;

	[[nodiscard]]
	iterator
	end() const;
private:
	sge::x11input::device::info::base info_base_;
};

}

#endif
