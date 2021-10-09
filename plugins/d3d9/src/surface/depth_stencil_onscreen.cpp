//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/devicefuncs/get_depth_stencil_surface.hpp>
#include <sge/d3d9/surface/depth_stencil_onscreen.hpp>
#include <sge/d3d9/surface/optional_d3d_ref.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <fcppt/optional/deref.hpp>

sge::d3d9::surface::depth_stencil_onscreen::depth_stencil_onscreen(IDirect3DDevice9 &_device)
    : sge::d3d9::resource(sge::d3d9::needs_reset::yes), device_(_device), surface_()
{
}

sge::d3d9::surface::depth_stencil_onscreen::~depth_stencil_onscreen() {}

sge::d3d9::surface::optional_d3d_ref sge::d3d9::surface::depth_stencil_onscreen::surface() const
{
  return fcppt::optional::deref(surface_);
}

void sge::d3d9::surface::depth_stencil_onscreen::init()
{
  surface_ = sge::d3d9::devicefuncs::get_depth_stencil_surface(device_);
}

void sge::d3d9::surface::depth_stencil_onscreen::on_loss()
{
  surface_ = sge::d3d9::surface::optional_d3d_unique_ptr();
}

void sge::d3d9::surface::depth_stencil_onscreen::on_reset() { this->init(); }
