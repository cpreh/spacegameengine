//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/lock_flags/read.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

bool sge::renderer::lock_flags::read(sge::renderer::lock_flags::method const _method)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_method)
  {
  case sge::renderer::lock_flags::method::read:
  case sge::renderer::lock_flags::method::readwrite:
    return true;
  case sge::renderer::lock_flags::method::write:
    return false;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_method);
}
