//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_SPOT_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_SPOT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/cutoff_angle.hpp>
#include <sge/renderer/state/ffp/lighting/light/direction.hpp>
#include <sge/renderer/state/ffp/lighting/light/position.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer::state::ffp::lighting::light
{

class spot
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  spot(
      sge::renderer::state::ffp::lighting::light::position,
      sge::renderer::state::ffp::lighting::light::direction,
      sge::renderer::state::ffp::lighting::light::cutoff_angle,
      sge::renderer::state::ffp::lighting::light::attenuation const &);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::ffp::lighting::light::position const &
      position() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::ffp::lighting::light::direction const &
      direction() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::lighting::light::cutoff_angle
  cutoff_angle() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::ffp::lighting::light::attenuation const &
      attenuation() const;

private:
  sge::renderer::state::ffp::lighting::light::position position_;

  sge::renderer::state::ffp::lighting::light::direction direction_;

  sge::renderer::state::ffp::lighting::light::cutoff_angle cutoff_angle_;

  sge::renderer::state::ffp::lighting::light::attenuation attenuation_;
};

}

#endif
