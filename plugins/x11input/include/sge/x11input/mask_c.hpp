//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_MASK_C_HPP_INCLUDED
#define SGE_X11INPUT_MASK_C_HPP_INCLUDED

#include <sge/x11input/mask_type.hpp>
#include <fcppt/bit/mask.hpp>
#include <fcppt/bit/mask_c.hpp>


namespace sge
{
namespace x11input
{

template<
	sge::x11input::mask_type Mask
>
inline
fcppt::bit::mask<
	sge::x11input::mask_type
>
mask_c()
{
	return
		fcppt::bit::mask_c<
			sge::x11input::mask_type,
			Mask
		>();
}

}
}

#endif
