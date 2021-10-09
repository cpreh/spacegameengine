//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_OP_FWD_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_OP_FWD_HPP_INCLUDED

#include <sge/renderer/state/ffp/sampler/binary_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>

namespace sge::renderer::state::ffp::sampler
{

using op = fcppt::variant::object<
    sge::renderer::state::ffp::sampler::unary_op,
    sge::renderer::state::ffp::sampler::binary_op,
    sge::renderer::state::ffp::sampler::ternary_op>;

}

#endif
