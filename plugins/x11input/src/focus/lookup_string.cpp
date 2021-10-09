//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/input/focus/char_type.hpp>
#include <sge/x11input/focus/char_vector.hpp>
#include <sge/x11input/focus/looked_up_string.hpp>
#include <sge/x11input/focus/lookup_string.hpp>
#include <sge/x11input/focus/translate_event.hpp>
#include <sge/x11input/key/translate_sym.hpp>
#include <sge/x11input/xim/context.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

int do_lookup(
    sge::x11input::xim::context const &_input_context,
    fcppt::reference<XKeyPressedEvent> const _event,
    wchar_t *const _data,
    int const _size,
    fcppt::reference<KeySym> const _key_sym,
    fcppt::reference<Status> const _status)
{
  return ::XwcLookupString(
      _input_context.get(), &_event.get(), _data, _size, &_key_sym.get(), &_status.get());
}

}

sge::x11input::focus::looked_up_string sge::x11input::focus::lookup_string(
    fcppt::log::object &_log,
    sge::x11input::xim::context const &_input_context,
    XIDeviceEvent const &_event)
{
  // TODO(philipp): Refactor this!

  XKeyPressedEvent xev(sge::x11input::focus::translate_event(_event));

  FCPPT_ASSERT_ERROR(xev.type == KeyPress);

  auto const get_size(
      [&_input_context, &xev]
      {
        Status status{};

        KeySym key_sym{NoSymbol};

        // first get the size needed
        int const needed_chars{::do_lookup(
            _input_context,
            fcppt::make_ref(xev),
            nullptr,
            0,
            fcppt::make_ref(key_sym),
            fcppt::make_ref(status))};

        FCPPT_ASSERT_ERROR(needed_chars == 0 || status == XBufferOverflow);

        return needed_chars;
      });

  using buffer_type = fcppt::container::buffer::object<sge::input::focus::char_type>;

  int const needed_chars{get_size()};

  buffer_type buffer{fcppt::cast::size<sge::x11input::focus::char_vector::size_type>(
      fcppt::cast::to_unsigned(needed_chars))};

  Status status{};

  KeySym key_sym{NoSymbol};

  int const chars_return(::do_lookup(
      _input_context,
      fcppt::make_ref(xev),
      buffer.write_data(),
      fcppt::cast::size<int>(fcppt::cast::to_signed(buffer.write_size())),
      fcppt::make_ref(key_sym),
      fcppt::make_ref(status)));

  FCPPT_ASSERT_ERROR(chars_return >= 0);

  // less chars might be returned here if the locale doesn't support it
  buffer.written(fcppt::cast::size<buffer_type::size_type>(fcppt::cast::to_unsigned(chars_return)));

  if (chars_return != needed_chars)
  {
    FCPPT_LOG_ERROR(
        _log,
        fcppt::log::out << FCPPT_TEXT("XwcLookupString mismatch of lengths!")
                FCPPT_TEXT(" This usually happens if your locale is not set."))
  }

  switch (status)
  {
  case XBufferOverflow:
    throw sge::input::exception(FCPPT_TEXT("XwcLookupString(): XBufferOverflow!"));
  case XLookupChars:
    return sge::x11input::focus::looked_up_string(
        fcppt::container::buffer::to_raw_vector(std::move(buffer)), sge::input::key::code::unknown);
  case XLookupKeySym:
    return sge::x11input::focus::looked_up_string(
        sge::x11input::focus::char_vector(), sge::x11input::key::translate_sym(key_sym));
  case XLookupBoth:
    return sge::x11input::focus::looked_up_string(
        fcppt::container::buffer::to_raw_vector(std::move(buffer)),
        sge::x11input::key::translate_sym(key_sym));
  case XLookupNone:
    return sge::x11input::focus::looked_up_string(
        sge::x11input::focus::char_vector(), sge::input::key::code::unknown);
  default:
    break;
  }

  throw sge::input::exception(FCPPT_TEXT("XwcLookupString(): Unknown return value!"));
}
