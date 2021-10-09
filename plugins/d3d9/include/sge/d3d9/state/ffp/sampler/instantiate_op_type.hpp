//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_FFP_SAMPLER_INSTANTIATE_OP_TYPE_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_SAMPLER_INSTANTIATE_OP_TYPE_HPP_INCLUDED

#include <sge/renderer/state/ffp/sampler/alpha_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/color_op_fwd.hpp>

#define SGE_D3D9_STATE_FFP_SAMPLER_INSTANTIATE_OP_TYPE(macro) \
  macro(sge::renderer::state::ffp::sampler::alpha_op); \
  macro(sge::renderer::state::ffp::sampler::color_op)

#endif
