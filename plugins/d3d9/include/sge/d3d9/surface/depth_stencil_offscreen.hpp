//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_SURFACE_DEPTH_STENCIL_OFFSCREEN_HPP_INCLUDED
#define SGE_D3D9_SURFACE_DEPTH_STENCIL_OFFSCREEN_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/multi_sample_quality.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/surface/depth_stencil_offscreen_fwd.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <sge/image/ds/format_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace surface
{

class depth_stencil_offscreen : public sge::renderer::depth_stencil_buffer::surface,
                                public sge::d3d9::resource
{
  FCPPT_NONCOPYABLE(depth_stencil_offscreen);

public:
  depth_stencil_offscreen(
      IDirect3DDevice9 &,
      sge::renderer::depth_stencil_buffer::surface_parameters const &,
      D3DMULTISAMPLE_TYPE,
      sge::d3d9::multi_sample_quality);

  ~depth_stencil_offscreen() override;

  dim size() const override;

  sge::image::ds::format format() const override;

  IDirect3DSurface9 &surface() const;

private:
  void init();

  void on_loss() override;

  void on_reset() override;

  IDirect3DDevice9 &device_;

  sge::renderer::depth_stencil_buffer::surface_parameters const parameters_;

  D3DMULTISAMPLE_TYPE const samples_;

  sge::d3d9::multi_sample_quality const multi_sample_quality_;

  sge::d3d9::surface::optional_d3d_unique_ptr surface_;
};

}
}
}

#endif
