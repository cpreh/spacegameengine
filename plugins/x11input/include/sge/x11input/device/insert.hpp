//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_INSERT_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INSERT_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/map.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{

template<
	typename Type
>
fcppt::shared_ptr<
	Type
>
insert(
	sge::x11input::device::map<
		Type
	> &_map,
	sge::x11input::device::id const _id,
	fcppt::shared_ptr<
		Type
	> _ptr
)
{
	FCPPT_ASSERT_ERROR(
		_map.insert(
			std::make_pair(
				_id,
				_ptr
			)
		).second
	);

	return
		_ptr;
}

}
}
}

#endif
