//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_CONVERT_SAMPLER_OP_HPP_INCLUDED
#define SGE_D3D9_STATE_CONVERT_SAMPLER_OP_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_type_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op_type_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_type_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace convert
{

D3DTEXTUREOP
sampler_op(sge::renderer::state::ffp::sampler::unary_op_type);

D3DTEXTUREOP
sampler_op(sge::renderer::state::ffp::sampler::binary_op_type);

D3DTEXTUREOP
sampler_op(sge::renderer::state::ffp::sampler::ternary_op_type);

}
}
}
}

#endif
