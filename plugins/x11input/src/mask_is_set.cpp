//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/mask_is_set.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <fcppt/config/external_end.hpp>

bool sge::x11input::mask_is_set(unsigned char const *const _ptr, int const _mask)
{
  // This macro casts the pointer to unsigned char * for whatever reason
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
  FCPPT_PP_DISABLE_GCC_WARNING(-Wcast-qual)
  FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE
  return XIMaskIsSet( // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-type-cstyle-cast,hicpp-signed-bitwise)
      _ptr,
      _mask);
  FCPPT_PP_POP_WARNING
}
