//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_TEXTURE_BASIC_IMPL_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_IMPL_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/color_format.hpp>
#include <sge/d3d9/texture/basic.hpp>
#include <sge/d3d9/texture/best_color_format.hpp>
#include <sge/d3d9/texture/pool.hpp>
#include <sge/d3d9/texture/usage.hpp>
#include <sge/d3d9/texturefuncs/get_level_count.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/translate_srgb_emulation.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>

template <typename Types>
sge::d3d9::texture::basic<Types>::basic(
    IDirect3DDevice9 &_device, parameters_type const &_parameters)
    : Types::base(),
      sge::d3d9::texture::base(),
      sge::d3d9::resource(
          sge::d3d9::texture::pool(_parameters.resource_flags(), _parameters.capabilities())),
      device_(_device),
      parameters_(_parameters),
      color_format_(sge::d3d9::texture::best_color_format(_parameters.format().format())),
      d3d_color_format_(sge::d3d9::convert::color_format(
          sge::renderer::texture::translate_srgb_emulation(sge::renderer::texture::color_format(
              color_format_, _parameters.format().emulate_srgb())))),
      usage_(sge::d3d9::texture::usage(_parameters.resource_flags(), _parameters.capabilities())),
      texture_()
{
  this->init();
}

template <typename Types>
sge::d3d9::texture::basic<Types>::~basic()
{
}

template <typename Types>
sge::renderer::resource_flags_field sge::d3d9::texture::basic<Types>::resource_flags() const
{
  return this->parameters().resource_flags();
}

template <typename Types>
sge::renderer::texture::capabilities_field sge::d3d9::texture::basic<Types>::capabilities() const
{
  return this->parameters().capabilities();
}

template <typename Types>
sge::renderer::texture::mipmap::object sge::d3d9::texture::basic<Types>::mipmap() const
{
  return this->parameters().mipmap();
}

template <typename Types>
void sge::d3d9::texture::basic<Types>::generate_mipmaps()
{
  this->get().GenerateMipSubLevels();
}

template <typename Types>
sge::renderer::texture::mipmap::level_count sge::d3d9::texture::basic<Types>::levels() const
{
  return sge::d3d9::texturefuncs::get_level_count(this->get());
}

template <typename Types>
typename sge::d3d9::texture::basic<Types>::d3d_type &sge::d3d9::texture::basic<Types>::get() const
{
  return *fcppt::optional::to_exception(
      this->texture_, [] { return sge::renderer::exception{FCPPT_TEXT("d3d9 texture not set!")}; });
}

template <typename Types>
sge::image::color::format sge::d3d9::texture::basic<Types>::color_format() const
{
  return color_format_;
}

template <typename Types>
typename sge::d3d9::texture::basic<Types>::parameters_type const &
sge::d3d9::texture::basic<Types>::parameters() const
{
  return parameters_;
}

template <typename Types>
typename sge::d3d9::texture::basic<Types>::d3d_unique_ptr
sge::d3d9::texture::basic<Types>::create(D3DPOOL const _pool, sge::d3d9::usage const _usage) const
{
  return Types::create(device_, this->parameters(), d3d_color_format_, _pool, _usage);
}

template <typename Types>
void sge::d3d9::texture::basic<Types>::init()
{
  texture_ = optional_d3d_unique_ptr(this->create(this->pool(), usage_));
}

template <typename Types>
void sge::d3d9::texture::basic<Types>::on_reset()
{
  texture_ = optional_d3d_unique_ptr();
}

template <typename Types>
void sge::d3d9::texture::basic<Types>::on_loss()
{
  this->init();
}

#endif
