//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/bool.hpp>
#include <sge/d3d9/devicefuncs/set_sampler_state.hpp>
#include <sge/d3d9/devicefuncs/set_texture.hpp>
#include <sge/d3d9/texture/base.hpp>
#include <sge/d3d9/texture/set.hpp>
#include <sge/image/color/format_is_srgb.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>

void sge::d3d9::texture::set(
    IDirect3DDevice9 &_device,
    sge::renderer::texture::stage const _stage,
    sge::renderer::texture::const_optional_base_ref const &_opt_base)
{
  sge::d3d9::devicefuncs::set_texture(_device, _stage, _opt_base);

  fcppt::optional::maybe_void(
      _opt_base,
      [&_device, _stage](fcppt::reference<sge::renderer::texture::base const> const _base)
      {
        sge::d3d9::devicefuncs::set_sampler_state(
            _device,
            _stage,
            D3DSAMP_SRGBTEXTURE,
            static_cast<DWORD>(sge::d3d9::convert::bool_(sge::image::color::format_is_srgb(
                dynamic_cast<sge::d3d9::texture::base const &>(_base.get()).color_format()))));
      });
}
