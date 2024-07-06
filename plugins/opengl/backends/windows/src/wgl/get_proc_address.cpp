//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/wgl/get_proc_address.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

PROC sge::opengl::wgl::get_proc_address(std::string const &_name)
{
  return ::wglGetProcAddress(_name.c_str());
}
