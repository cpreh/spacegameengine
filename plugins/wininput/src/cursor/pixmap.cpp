//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/wininput/cursor/pixmap.hpp>
#include <awl/backends/windows/module_handle.hpp>
#include <awl/backends/windows/system_metrics.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>

sge::wininput::cursor::pixmap::pixmap()
    : cursor_(
          []
          {
            int const cursor_width{awl::backends::windows::system_metrics(SM_CXCURSOR)};
            int const cursor_height{awl::backends::windows::system_metrics(SM_CYCURSOR)};

            using byte_vector = std::vector<BYTE>;

            static_assert(std::is_unsigned_v<BYTE>, "BYTE should be unsigned");

            byte_vector::size_type const size{fcppt::optional::to_exception(
                fcppt::math::ceil_div(
                    fcppt::cast::size<byte_vector::size_type>(
                        fcppt::cast::to_unsigned(cursor_width * cursor_height)),
                    fcppt::cast::size<byte_vector::size_type>(std::numeric_limits<BYTE>::digits)),
                [] { return sge::input::exception{FCPPT_TEXT("Div by zero!")}; })};

            byte_vector const and_values(size, std::numeric_limits<BYTE>::max());
            byte_vector const xor_values(size, fcppt::literal<BYTE>(0u));

            return ::CreateCursor(
                awl::backends::windows::module_handle(),
                0,
                0,
                cursor_width,
                cursor_height,
                and_values.data(),
                xor_values.data());
          }())
{
  if (this->cursor_ == NULL)
  {
    throw sge::input::exception(FCPPT_TEXT("CreateCursor() failed!"));
  }
}

sge::wininput::cursor::pixmap::~pixmap() { ::DestroyCursor(this->cursor_); }

HCURSOR
sge::wininput::cursor::pixmap::get() const { return this->cursor_; }
