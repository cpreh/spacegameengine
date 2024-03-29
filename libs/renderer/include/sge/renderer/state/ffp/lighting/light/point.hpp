//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_POINT_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_POINT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/point_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/state/ffp/lighting/light/position.hpp>

namespace sge::renderer::state::ffp::lighting::light
{

class point
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  point(
      sge::renderer::state::ffp::lighting::light::position,
      sge::renderer::state::ffp::lighting::light::attenuation const &);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::ffp::lighting::light::position const &
      position() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::ffp::lighting::light::attenuation const &
      attenuation() const;

private:
  sge::renderer::state::ffp::lighting::light::position position_;

  sge::renderer::state::ffp::lighting::light::attenuation attenuation_;
};

}

#endif
