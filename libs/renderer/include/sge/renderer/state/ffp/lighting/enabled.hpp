//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_ENABLED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_ENABLED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_from_vertex.hpp>
#include <sge/renderer/state/ffp/lighting/enabled_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer::state::ffp::lighting
{

class enabled
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  enabled(
      sge::renderer::state::ffp::lighting::ambient_color,
      sge::renderer::state::ffp::lighting::diffuse_from_vertex);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::ffp::lighting::ambient_color const &
      ambient_color() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::lighting::diffuse_from_vertex
  diffuse_from_vertex() const;

private:
  sge::renderer::state::ffp::lighting::ambient_color ambient_color_;

  sge::renderer::state::ffp::lighting::diffuse_from_vertex diffuse_from_vertex_;
};

}

#endif
