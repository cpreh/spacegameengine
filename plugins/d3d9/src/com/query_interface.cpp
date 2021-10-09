//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/com/query_interface.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void *sge::d3d9::com::query_interface(IUnknown &_obj, REFIID _id)
{
  void *result;

  if (_obj.QueryInterface(_id, &result) != S_OK)
    throw sge::renderer::exception(FCPPT_TEXT("QueryInterface failed!"));

  return result;
}
