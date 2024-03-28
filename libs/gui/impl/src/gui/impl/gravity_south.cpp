//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/gravity.hpp>
#include <sge/gui/impl/gravity_south.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

bool sge::gui::impl::gravity_south(sge::gui::gravity const _gravity)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_gravity)
  {
  case sge::gui::gravity::north_east:
  case sge::gui::gravity::north_west:
    return false;
  case sge::gui::gravity::south_east:
  case sge::gui::gravity::south_west:
    return true;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_gravity);
}
