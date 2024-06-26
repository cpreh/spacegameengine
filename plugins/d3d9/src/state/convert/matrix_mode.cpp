//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/matrix_mode.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

D3DTRANSFORMSTATETYPE
sge::d3d9::state::convert::matrix_mode(sge::renderer::state::ffp::transform::mode const _mode)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_mode)
  {
  case sge::renderer::state::ffp::transform::mode::world:
    return D3DTS_VIEW;
  case sge::renderer::state::ffp::transform::mode::projection:
    return D3DTS_PROJECTION;
  case sge::renderer::state::ffp::transform::mode::texture:
    return D3DTS_TEXTURE0;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_mode);
}
