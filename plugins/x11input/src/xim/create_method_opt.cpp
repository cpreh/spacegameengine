//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/x11input/xim/create_method.hpp>
#include <sge/x11input/xim/create_method_opt.hpp>
#include <sge/x11input/xim/get_supported_styles.hpp>
#include <sge/x11input/xim/method.hpp>
#include <sge/x11input/xim/method_unique_ptr.hpp>
#include <sge/x11input/xim/optional_method_unique_ptr.hpp>
#include <sge/x11input/xim/supported_styles_unique_ptr.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains_if.hpp>
#include <fcppt/bit/mask_c.hpp>
#include <fcppt/bit/test.hpp>
#include <fcppt/iterator/make_range.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::x11input::xim::optional_method_unique_ptr sge::x11input::xim::create_method_opt(
    fcppt::log::object &_log, awl::backends::x11::display_ref const _display)
try
{
  sge::x11input::xim::method_unique_ptr result{sge::x11input::xim::create_method(_log, _display)};

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

  sge::x11input::xim::supported_styles_unique_ptr const styles{
      sge::x11input::xim::get_supported_styles(*result)};

  if (fcppt::algorithm::contains_if(
          fcppt::iterator::make_range(
              styles->supported_styles,
              styles->supported_styles + // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                  styles->count_styles),
          [](XIMStyle const &_style)
          {
            return fcppt::bit::test(_style, fcppt::bit::mask_c<XIMStyle, XIMPreeditNothing>()) &&
                   fcppt::bit::test(_style, fcppt::bit::mask_c<XIMStyle, XIMStatusNothing>());
          }))
  {
    return sge::x11input::xim::optional_method_unique_ptr{std::move(result)};
  }

FCPPT_PP_POP_WARNING

  FCPPT_LOG_ERROR(
      _log,
      fcppt::log::out << FCPPT_TEXT(
          "The selected XIM IME does not support PreeditNothing | StatusNothing!"))

  return sge::x11input::xim::optional_method_unique_ptr{};
}
catch (sge::input::exception const &_error)
{
  FCPPT_LOG_ERROR(_log, fcppt::log::out << FCPPT_TEXT("Failed to open XIM: ") << _error.string())

  return sge::x11input::xim::optional_method_unique_ptr();
}
