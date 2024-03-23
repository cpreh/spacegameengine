//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/color_bits.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::renderer::pixel_format::bit_count
sge::renderer::pixel_format::color_bits(sge::renderer::pixel_format::color const _format)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
  case sge::renderer::pixel_format::color::depth16:
    return sge::renderer::pixel_format::bit_count(
        16U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    );
  case sge::renderer::pixel_format::color::depth32:
    return sge::renderer::pixel_format::bit_count(
        32U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    );
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
