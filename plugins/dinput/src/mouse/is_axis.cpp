//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/mouse/is_axis.hpp>

bool sge::dinput::mouse::is_axis(GUID const _guid)
{
  return _guid == GUID_XAxis || _guid == GUID_YAxis || _guid == GUID_ZAxis;
}
