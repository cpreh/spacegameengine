//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/source_blend_func.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

D3DBLEND
sge::d3d9::state::convert::source_blend_func(sge::renderer::state::core::blend::source const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sge::renderer::state::core::blend::source::zero:
    return D3DBLEND_ZERO;
  case sge::renderer::state::core::blend::source::one:
    return D3DBLEND_ONE;
  case sge::renderer::state::core::blend::source::dest_color:
    return D3DBLEND_DESTCOLOR;
  case sge::renderer::state::core::blend::source::inv_dest_color:
    return D3DBLEND_INVDESTCOLOR;
  case sge::renderer::state::core::blend::source::src_alpha:
    return D3DBLEND_SRCALPHA;
  case sge::renderer::state::core::blend::source::inv_src_alpha:
    return D3DBLEND_INVSRCALPHA;
  case sge::renderer::state::core::blend::source::dest_alpha:
    return D3DBLEND_DESTALPHA;
  case sge::renderer::state::core::blend::source::inv_dest_alpha:
    return D3DBLEND_INVDESTALPHA;
  case sge::renderer::state::core::blend::source::src_alpha_sat:
    return D3DBLEND_SRCALPHASAT;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
