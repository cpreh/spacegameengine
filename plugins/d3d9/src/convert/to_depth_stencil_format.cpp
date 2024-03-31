//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_depth_stencil_format.hpp>
#include <sge/image/ds/format.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::image::ds::format sge::d3d9::convert::to_depth_stencil_format(D3DFORMAT const _format)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
  case D3DFMT_D16:
    return sge::image::ds::format::d16;
  case D3DFMT_D24S8:
    return sge::image::ds::format::d24s8;
  case D3DFMT_D32:
    return sge::image::ds::format::d32;
  default:
    break;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
