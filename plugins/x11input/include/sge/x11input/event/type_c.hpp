//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_EVENT_TYPE_C_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_TYPE_C_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::event
{

template <int Type>
using type_c = std::integral_constant<int, Type>;

}

#endif
