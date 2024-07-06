//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/glx/optional_raw_function.hpp>
#include <sge/opengl/glx/proc_address.hpp>
#include <sge/opengl/glx/proc_address_function.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/optional/from_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

sge::opengl::glx::optional_raw_function sge::opengl::glx::proc_address(
    sge::opengl::glx::proc_address_function _proc_address, std::string const &_name)
{
  return fcppt::optional::from_pointer(
      _proc_address(fcppt::cast::to_char_ptr<unsigned char const *>(_name.c_str())));
}
