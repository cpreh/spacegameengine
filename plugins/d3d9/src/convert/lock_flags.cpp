//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/lock_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::d3d9::lock_flags sge::d3d9::convert::lock_flags(
    sge::renderer::lock_flags::method const _method,
    sge::renderer::resource_flags_field const &_flags)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_method)
  {
  case sge::renderer::lock_flags::method::read:
    return fcppt::strong_typedef_construct_cast<sge::d3d9::lock_flags, fcppt::cast::size_fun>(
        fcppt::cast::to_unsigned(D3DLOCK_READONLY));
  case sge::renderer::lock_flags::method::write:
    if (_flags & sge::renderer::resource_flags::dynamic)
      return fcppt::strong_typedef_construct_cast<sge::d3d9::lock_flags, fcppt::cast::size_fun>(
          fcppt::cast::to_unsigned(D3DLOCK_DISCARD));
    // fall through
  case sge::renderer::lock_flags::method::readwrite:
    return sge::d3d9::lock_flags(0u);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_method);
}
