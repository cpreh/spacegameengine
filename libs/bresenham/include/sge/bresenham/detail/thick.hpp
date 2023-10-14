//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_BRESENHAM_DETAIL_THICK_HPP_INCLUDED
#define SGE_BRESENHAM_DETAIL_THICK_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::bresenham::detail
{

template <bool Thick, typename Callback, typename T>
[[nodiscard]] inline std::enable_if_t<Thick, bool>
thick(Callback const &_callback, T const _x, T const _y)
{
  return _callback(_x, _y);
}

template <bool Thick, typename Callback, typename T>
[[nodiscard]] inline std::enable_if_t<!Thick, bool> thick(Callback const &, T, T)
{
  return true;
}

}

#endif
