//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_CONVERT_SAMPLER_OP_TYPE_HPP_INCLUDED
#define SGE_D3D9_STATE_CONVERT_SAMPLER_OP_TYPE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/color_op_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace convert
{

template <typename OpType>
struct sampler_op_type;

template <>
struct sampler_op_type<sge::renderer::state::ffp::sampler::alpha_op>
{
  static D3DTEXTURESTAGESTATETYPE get();
};

template <>
struct sampler_op_type<sge::renderer::state::ffp::sampler::color_op>
{
  static D3DTEXTURESTAGESTATETYPE get();
};

}
}
}
}

#endif
