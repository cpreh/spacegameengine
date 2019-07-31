//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WININPUT_CURSOR_CLIP_HPP_INCLUDED
#define SGE_WININPUT_CURSOR_CLIP_HPP_INCLUDED

#include <awl/backends/windows/optional_rect_fwd.hpp>


namespace sge
{
namespace wininput
{
namespace cursor
{

bool
clip(
	awl::backends::windows::optional_rect const &
);

}
}
}

#endif
