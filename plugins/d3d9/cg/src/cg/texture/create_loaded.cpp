//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/texture/create_loaded.hpp>
#include <sge/d3d9/cg/texture/loaded_object.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::renderer::cg::loaded_texture_unique_ptr sge::d3d9::cg::texture::create_loaded(
    IDirect3DDevice9 &_device,
    sge::cg::parameter::object const &_parameter,
    sge::renderer::texture::base &_texture,
    sge::renderer::caps::texture_stages const _texture_stages)
{
  return fcppt::unique_ptr_to_base<sge::renderer::cg::loaded_texture>(
      fcppt::make_unique_ptr<sge::d3d9::cg::texture::loaded_object>(
          _device, _parameter, _texture, _texture_stages));
}
