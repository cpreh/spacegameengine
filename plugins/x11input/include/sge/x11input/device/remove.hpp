//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_REMOVE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_REMOVE_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/map.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/find_opt_iterator.hpp>


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
remove(
	fcppt::reference<
		sge::x11input::device::map<
			Type
		>
	> const _map,
	sge::x11input::device::id const _id
)
{
	using
	iterator_type
	=
	typename
	sge::x11input::device::map<
		Type
	>::iterator;

	iterator_type const iterator{
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::find_opt_iterator(
				_map.get(),
				_id
			)
		)
	};

	fcppt::shared_ptr<
		Type
	>
	result{
		iterator->second
	};

	_map.get().erase(
		iterator
	);

	return
		result;
}

}
}
}

#endif
