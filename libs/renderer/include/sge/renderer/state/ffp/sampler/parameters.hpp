//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>

namespace sge::renderer::state::ffp::sampler
{

class parameters
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  parameters(
      sge::renderer::state::ffp::sampler::color_op, sge::renderer::state::ffp::sampler::alpha_op);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::sampler::color_op
  color_op() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::sampler::alpha_op
  alpha_op() const;

private:
  sge::renderer::state::ffp::sampler::color_op color_op_;

  sge::renderer::state::ffp::sampler::alpha_op alpha_op_;
};

}

#endif
