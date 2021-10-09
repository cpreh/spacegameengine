//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <sge/d3d9/devicefuncs/set_depth_stencil_surface.hpp>
#include <sge/d3d9/devicefuncs/set_render_target.hpp>
#include <sge/d3d9/surface/color.hpp>
#include <sge/d3d9/surface/color_onscreen_target.hpp>
#include <sge/d3d9/surface/depth_stencil_onscreen.hpp>
#include <sge/d3d9/surface/optional_d3d_ref.hpp>
#include <sge/d3d9/target/basic_impl.hpp>
#include <sge/d3d9/target/onscreen.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/color_buffer/readable_surface_fwd.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>

sge::d3d9::target::onscreen::onscreen(
    IDirect3DDevice9 &_device,
    sge::image::color::format const _color_format,
    sge::renderer::target::viewport const &_viewport,
    sge::d3d9::resource_manager &_resources,
    sge::renderer::caps::target_surface_indices const _max_surfaces)
    : base(_device, _viewport, _max_surfaces),
      color_surface_(fcppt::make_unique_ptr<sge::d3d9::surface::color>(
          _device, _color_format, sge::d3d9::surface::color_onscreen_target(_device))),
      depth_stencil_surface_(
          fcppt::make_unique_ptr<sge::d3d9::surface::depth_stencil_onscreen>(_device))
{
  _resources.add(*color_surface_);

  _resources.add(*depth_stencil_surface_);
}

sge::d3d9::target::onscreen::~onscreen() {}

sge::renderer::color_buffer::readable_surface const &sge::d3d9::target::onscreen::surface() const
{
  return *color_surface_;
}

bool sge::d3d9::target::onscreen::needs_present() const { return true; }

void sge::d3d9::target::onscreen::on_activate()
{
  sge::d3d9::devicefuncs::set_render_target(
      this->device(),
      sge::renderer::target::surface_index(0u),
      sge::d3d9::surface::optional_d3d_ref(fcppt::make_ref(color_surface_->surface())));

  sge::d3d9::devicefuncs::set_depth_stencil_surface(
      this->device(), depth_stencil_surface_->surface());
}

void sge::d3d9::target::onscreen::on_deactivate()
{
  // Don't deactivate the 0th color surface because D3D9 doesn't allow it

  sge::d3d9::devicefuncs::set_depth_stencil_surface(
      this->device(), sge::d3d9::surface::optional_d3d_ref());
}

template class sge::d3d9::target::basic<sge::renderer::target::onscreen>;
