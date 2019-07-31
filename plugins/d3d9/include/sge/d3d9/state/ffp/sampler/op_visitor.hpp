//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_FFP_SAMPLER_OP_VISITOR_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_SAMPLER_OP_VISITOR_HPP_INCLUDED

#include <sge/d3d9/state/ffp/sampler/state_vector.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace sampler
{

template<
        typename OpType
>
class op_visitor
{
public:
        typedef sge::d3d9::state::ffp::sampler::state_vector result_type;

        result_type
        operator()(
                sge::renderer::state::ffp::sampler::unary_op const &
        ) const;

        result_type
        operator()(
                sge::renderer::state::ffp::sampler::binary_op const &
        ) const;

        result_type
        operator()(
                sge::renderer::state::ffp::sampler::ternary_op const &
        ) const;
};

}
}
}
}
}

#endif
