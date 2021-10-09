//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/exception.hpp>
#include <sge/gdifont/device_context.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/select_object.hpp>
#include <fcppt/text.hpp>

HGDIOBJ
sge::gdifont::select_object(
    sge::gdifont::device_context const &_device_context, HGDIOBJ const _object)
{
  HGDIOBJ const result(::SelectObject(_device_context.get(), _object));

  if (result == nullptr || result == HGDI_ERROR)
    throw sge::font::exception(FCPPT_TEXT("SelectObject failed!"));

  return result;
}
