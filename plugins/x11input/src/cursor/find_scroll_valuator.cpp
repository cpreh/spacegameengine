//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/x11input/cursor/find_scroll_valuator.hpp>
#include <sge/x11input/device/info/class_maybe.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

XIValuatorClassInfo const &sge::x11input::cursor::find_scroll_valuator(
    sge::x11input::device::valuator::index const _number, XIDeviceInfo const &_info)
{
  return fcppt::optional::to_exception(
             fcppt::algorithm::find_by_opt<fcppt::reference<XIValuatorClassInfo const>>(
                 fcppt::make_int_range_count(_info.num_classes),
                 [_number, &_info](int const _index)
                 {
                   return fcppt::optional::bind(
                       sge::x11input::device::info::class_maybe<XIValuatorClassInfo>(
                           // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                           *_info.classes[_index]),
                       [_number](fcppt::reference<XIValuatorClassInfo const> const _valuator_class)
                       {
                         using result_type = fcppt::optional::reference<XIValuatorClassInfo const>;

                         return _valuator_class.get().number == _number.get()
                                    ? result_type(_valuator_class)
                                    : result_type();
                       });
                 }),
             [] { return sge::input::exception{FCPPT_TEXT("Scroll valuator not present")}; })
      .get();
}

FCPPT_PP_POP_WARNING
