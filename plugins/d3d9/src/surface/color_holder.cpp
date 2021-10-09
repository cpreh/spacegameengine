//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/color_holder.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/surfacefuncs/dim.hpp>
#include <sge/d3d9/surfacefuncs/is_render_target.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::d3d9::surface::color_holder::color_holder(sge::d3d9::surface::d3d_unique_ptr &&_surface)
    : surface_(std::move(_surface)),
      size_(sge::d3d9::surfacefuncs::dim(*surface_)),
      is_render_target_(sge::d3d9::surfacefuncs::is_render_target(*surface_))
{
}

sge::d3d9::surface::color_holder::~color_holder() {}

IDirect3DSurface9 &sge::d3d9::surface::color_holder::get() const { return *surface_; }

sge::renderer::dim2 const &sge::d3d9::surface::color_holder::size() const { return size_; }

bool sge::d3d9::surface::color_holder::is_render_target() const { return is_render_target_; }
