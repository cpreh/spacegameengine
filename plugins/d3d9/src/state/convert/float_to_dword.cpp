//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/float_to_dword.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>

DWORD
sge::d3d9::state::convert::float_to_dword(float const _value)
{
  static_assert(sizeof(float) == sizeof(DWORD), "float and DWORD must be of the same size");

  DWORD dest;

  std::memcpy(&dest, &_value, sizeof(DWORD));

  return dest;
}
