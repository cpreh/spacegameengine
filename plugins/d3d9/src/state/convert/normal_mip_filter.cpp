//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/normal_mip_filter.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

DWORD
sge::d3d9::state::convert::normal_mip_filter(
    sge::renderer::state::core::sampler::filter::normal::mip const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sge::renderer::state::core::sampler::filter::normal::mip::off:
    return D3DTEXF_NONE;
  case sge::renderer::state::core::sampler::filter::normal::mip::point:
    return D3DTEXF_POINT;
  case sge::renderer::state::core::sampler::filter::normal::mip::linear:
    return D3DTEXF_LINEAR;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
