//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_MAP_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_MAP_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/strong_typedef_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
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
using
map
=
std::unordered_map<
	sge::x11input::device::id,
	fcppt::shared_ptr<
		Type
	>
>;

}
}
}

#endif
