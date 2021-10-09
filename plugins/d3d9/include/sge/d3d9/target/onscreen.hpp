//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_TARGET_ONSCREEN_HPP_INCLUDED
#define SGE_D3D9_TARGET_ONSCREEN_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource_manager_fwd.hpp>
#include <sge/d3d9/surface/color_fwd.hpp>
#include <sge/d3d9/surface/depth_stencil_onscreen_fwd.hpp>
#include <sge/d3d9/target/basic.hpp>
#include <sge/d3d9/target/onscreen_fwd.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/color_buffer/readable_surface_fwd.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>

namespace sge
{
namespace d3d9
{
namespace target
{

class onscreen : public sge::d3d9::target::basic<sge::renderer::target::onscreen>
{
  FCPPT_NONCOPYABLE(onscreen);

  typedef sge::d3d9::target::basic<sge::renderer::target::onscreen> base;

public:
  onscreen(
      IDirect3DDevice9 &,
      sge::image::color::format,
      sge::renderer::target::viewport const &,
      sge::d3d9::resource_manager &,
      sge::renderer::caps::target_surface_indices);

  ~onscreen() override;

  sge::renderer::color_buffer::readable_surface const &surface() const override;

private:
  bool needs_present() const override;

  void on_activate() override;

  void on_deactivate() override;

  typedef fcppt::unique_ptr<sge::d3d9::surface::color> color_surface_unique_ptr;

  color_surface_unique_ptr const color_surface_;

  typedef fcppt::unique_ptr<sge::d3d9::surface::depth_stencil_onscreen>
      depth_stencil_surface_unique_ptr;

  depth_stencil_surface_unique_ptr const depth_stencil_surface_;
};

}
}
}

#endif
