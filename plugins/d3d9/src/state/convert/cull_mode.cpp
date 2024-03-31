//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

D3DCULL
sge::d3d9::state::convert::cull_mode(sge::renderer::state::core::rasterizer::cull_mode const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sge::renderer::state::core::rasterizer::cull_mode::off:
    return D3DCULL_NONE;
  case sge::renderer::state::core::rasterizer::cull_mode::clockwise:
    return D3DCULL_CW;
  case sge::renderer::state::core::rasterizer::cull_mode::counter_clockwise:
    return D3DCULL_CCW;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
