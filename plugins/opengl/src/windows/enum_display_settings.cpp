//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/windows/enum_display_settings.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>

DEVMODE const sge::opengl::windows::enum_display_settings(LPCTSTR const _name, UINT const _num)
{
  DEVMODE result;

  if (EnumDisplaySettings(_name, _num, &result) == 0)
    throw sge::renderer::exception(FCPPT_TEXT("EnumDisplaySettings failed"));

  return result;
}
