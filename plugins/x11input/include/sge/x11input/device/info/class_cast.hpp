//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_INFO_CLASS_CAST_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_CLASS_CAST_HPP_INCLUDED

#include <fcppt/mpl/list/contains.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::device::info
{

template <typename Result>
Result class_cast(XIAnyClassInfo const &_info)
  requires(fcppt::mpl::list::contains<
           fcppt::mpl::list::
               object<XIButtonClassInfo, XIValuatorClassInfo, XIKeyClassInfo, XIScrollClassInfo>,
           std::remove_cvref_t<Result>>::value)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wstrict-aliasing)

  return
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      reinterpret_cast<Result>(_info);

  FCPPT_PP_POP_WARNING
}
}

#endif
