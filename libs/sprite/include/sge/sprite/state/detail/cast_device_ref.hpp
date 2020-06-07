//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_CAST_DEVICE_REF_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_CAST_DEVICE_REF_HPP_INCLUDED

#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/state/detail/device_for_state.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename State,
	typename Device
>
fcppt::reference<
	sge::sprite::state::detail::device_for_state<
		State
	>
>
cast_device_ref(
	fcppt::reference<
		Device
	> const _device
)
{
	return
		fcppt::reference<
			sge::sprite::state::detail::device_for_state<
				State
			>
		>{
			// TODO(philipp): reference::map
			_device.get()
		};
}

}
}
}
}

#endif
