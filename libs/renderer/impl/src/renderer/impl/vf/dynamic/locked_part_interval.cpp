//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <sge/renderer/impl/vf/dynamic/locked_part_interval.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>
#include <fcppt/preprocessor/disable_gnu_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::renderer::impl::vf::dynamic::lock_interval
sge::renderer::impl::vf::dynamic::locked_part_interval(
    sge::renderer::vf::dynamic::locked_part const &_locked_part)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GNU_GCC_WARNING(-Wzero-as-null-pointer-constant)

  return sge::renderer::impl::vf::dynamic::lock_interval(
      _locked_part.pos().get(), _locked_part.pos().get() + _locked_part.count().get());

  FCPPT_PP_POP_WARNING
}
