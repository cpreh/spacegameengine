//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_RENDER_CONTEXT_PARAMETERS_HPP_INCLUDED
#define SGE_D3D9_RENDER_CONTEXT_PARAMETERS_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/render_context/parameters_fwd.hpp>
#include <sge/d3d9/state/core/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge
{
namespace d3d9
{
namespace render_context
{

class parameters
{
public:
  parameters(
      IDirect3DDevice9 &,
      sge::renderer::target::base &,
      sge::renderer::caps::texture_stages,
      sge::renderer::caps::light_indices,
      sge::d3d9::state::core::defaults const &,
      sge::d3d9::state::ffp::defaults const &);

  IDirect3DDevice9 &device() const;

  sge::renderer::target::base &target() const;

  sge::renderer::caps::texture_stages const texture_stages() const;

  sge::renderer::caps::light_indices const light_indices() const;

  sge::d3d9::state::core::defaults const &core_defaults() const;

  sge::d3d9::state::ffp::defaults const &ffp_defaults() const;

private:
  fcppt::reference<IDirect3DDevice9> device_;

  fcppt::reference<sge::renderer::target::base> target_;

  sge::renderer::caps::texture_stages texture_stages_;

  sge::renderer::caps::light_indices light_indices_;

  fcppt::reference<sge::d3d9::state::core::defaults const> core_defaults_;

  fcppt::reference<sge::d3d9::state::ffp::defaults const> ffp_defaults_;
};

}
}
}

#endif
