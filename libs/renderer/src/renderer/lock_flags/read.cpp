//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/lock_flags/read.hpp>
#include <fcppt/assert/unreachable.hpp>

bool sge::renderer::lock_flags::read(sge::renderer::lock_flags::method const _method)
{
  switch (_method)
  {
  case sge::renderer::lock_flags::method::read:
  case sge::renderer::lock_flags::method::readwrite:
    return true;
  case sge::renderer::lock_flags::method::write:
    return false;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
