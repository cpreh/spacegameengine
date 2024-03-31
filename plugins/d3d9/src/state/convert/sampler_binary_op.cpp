//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/sampler_binary_op.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_type.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

D3DTEXTUREOP
sge::d3d9::state::convert::sampler_binary_op(
    sge::renderer::state::ffp::sampler::binary_op_type const _op)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_op)
  {
  case sge::renderer::state::ffp::sampler::binary_op_type::modulate:
    return D3DTOP_MODULATE;
  case sge::renderer::state::ffp::sampler::binary_op_type::add:
    return D3DTOP_ADD;
  case sge::renderer::state::ffp::sampler::binary_op_type::subtract:
    return D3DTOP_SUBTRACT;
  case sge::renderer::state::ffp::sampler::binary_op_type::add_signed:
    return D3DTOP_ADDSIGNED;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_op);
}
