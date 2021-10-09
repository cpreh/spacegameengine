//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_PARAMETERS_BOTH_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_PARAMETERS_BOTH_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/sampler/op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>

namespace sge::renderer::state::ffp::sampler
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::state::ffp::sampler::parameters
parameters_both(sge::renderer::state::ffp::sampler::op const &);

}

#endif
