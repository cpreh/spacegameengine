//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_SURFACE_COLOR_HOLDER_HPP_INCLUDED
#define SGE_D3D9_SURFACE_COLOR_HOLDER_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/color_holder_fwd.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace surface
{

class color_holder
{
  FCPPT_NONCOPYABLE(color_holder);

public:
  explicit color_holder(sge::d3d9::surface::d3d_unique_ptr &&);

  ~color_holder();

  IDirect3DSurface9 &get() const;

  sge::renderer::dim2 const &size() const;

  bool is_render_target() const;

private:
  sge::d3d9::surface::d3d_unique_ptr const surface_;

  sge::renderer::dim2 const size_;

  bool const is_render_target_;
};

}
}
}

#endif
