//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_ATTENUATION_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_ATTENUATION_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/light/attenuation_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/state/ffp/lighting/light/constant_attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/linear_attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/quadratic_attenuation.hpp>

namespace sge::renderer::state::ffp::lighting::light
{

class attenuation
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  attenuation(
      sge::renderer::state::ffp::lighting::light::constant_attenuation,
      sge::renderer::state::ffp::lighting::light::linear_attenuation,
      sge::renderer::state::ffp::lighting::light::quadratic_attenuation);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::ffp::lighting::light::constant_attenuation
      constant() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::ffp::lighting::light::linear_attenuation
      linear() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::ffp::lighting::light::quadratic_attenuation
      quadratic() const;

private:
  sge::renderer::state::ffp::lighting::light::constant_attenuation constant_;

  sge::renderer::state::ffp::lighting::light::linear_attenuation linear_;

  sge::renderer::state::ffp::lighting::light::quadratic_attenuation quadratic_;
};

}

#endif
