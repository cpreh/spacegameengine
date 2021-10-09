//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_TEXTURE_BASE_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texture/base_fwd.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace texture
{

class base
{
  FCPPT_NONCOPYABLE(base);

protected:
  base();

  virtual ~base();

public:
  virtual IDirect3DBaseTexture9 &get() const = 0;

  virtual sge::image::color::format color_format() const = 0;
};

}
}
}

#endif
