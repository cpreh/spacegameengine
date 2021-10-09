//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_CORE_DEPTH_STENCIL_STENCIL_VISITOR_HPP_INCLUDED
#define SGE_D3D9_STATE_CORE_DEPTH_STENCIL_STENCIL_VISITOR_HPP_INCLUDED

#include <sge/d3d9/state/render_vector.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace core
{
namespace depth_stencil
{
namespace stencil
{

class visitor
{
public:
  typedef sge::d3d9::state::render_vector result_type;

  result_type operator()(sge::renderer::state::core::depth_stencil::stencil::off const &) const;

  result_type operator()(sge::renderer::state::core::depth_stencil::stencil::enabled const &) const;
};

}
}
}
}
}
}

#endif
