//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::renderer::lock_flags::method
sge::renderer::lock_flags::from_mode(sge::renderer::lock_mode const _mode)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_mode)
  {
  case sge::renderer::lock_mode::writeonly:
    return sge::renderer::lock_flags::method::write;
  case sge::renderer::lock_mode::readwrite:
    return sge::renderer::lock_flags::method::readwrite;
  }

  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_mode);
}
