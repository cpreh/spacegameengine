//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_DETAIL_RENDERER_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_RENDERER_HPP_INCLUDED

#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/detail/renderer_fwd.hpp> // IWYU pragma: keep
#include <sge/systems/detail/symbol.hpp>

namespace sge::systems::detail
{

class renderer
{
public:
  SGE_SYSTEMS_DETAIL_SYMBOL
  renderer(sge::systems::renderer &&, sge::systems::renderer_caps);

  [[nodiscard]] sge::systems::renderer const &parameters() const;

  [[nodiscard]] sge::systems::renderer_caps caps() const;

private:
  sge::systems::renderer parameters_;

  sge::systems::renderer_caps caps_;
};

}

#endif
