//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/com/compare.hpp>
#include <sge/d3d9/com/query_interface.hpp>

bool sge::d3d9::com::compare(IUnknown &_obj1, IUnknown &_obj2)
{
  return sge::d3d9::com::query_interface(_obj1, IID_IUnknown) ==
         sge::d3d9::com::query_interface(_obj2, IID_IUnknown);
}
