//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/select_unsafe.hpp>
#include <sge/x11input/event/type.hpp>
#include <sge/x11input/event/type_container.hpp>
#include <awl/backends/x11/display.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/init.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

void sge::x11input::event::select_unsafe(
    awl::backends::x11::window::base const &_window,
    sge::x11input::device::id const _device,
    sge::x11input::event::type_container const &_types)
{
  if (_window.destroyed())
  {
    return;
  }

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
  FCPPT_PP_DISABLE_GCC_WARNING(-Wconversion)
  using mask_type = fcppt::array::object<
      unsigned char,
      XIMaskLen(XI_LASTEVENT) // NOLINT(hicpp-signed-bitwise)
      >;
  FCPPT_PP_POP_WARNING

  auto mask_data(
      fcppt::array::init<mask_type>([](auto) { return fcppt::literal<unsigned char>(0); }));

  for (sge::x11input::event::type const &event : _types)
  {
    FCPPT_PP_PUSH_WARNING
    FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
    FCPPT_PP_DISABLE_GCC_WARNING(-Wconversion)
    FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE
    XISetMask( // NOLINT(hicpp-signed-bitwise, cppcoreguidelines-pro-bounds-pointer-arithmetic)
        mask_data.data(),
        event.get());
    FCPPT_PP_POP_WARNING
  }

  XIEventMask mask{
      _device.get(),
      fcppt::cast::size<int>(fcppt::cast::to_signed(mask_data.size())),
      mask_data.data()};

  if (::XISelectEvents(_window.display().get().get(), _window.get(), &mask, 1) != 0)
  {
    throw sge::input::exception{FCPPT_TEXT("XISelectEvents failed!")};
  }
}
