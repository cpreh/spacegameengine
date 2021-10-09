//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/mipmap/generate.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>

template <typename Types>
sge::opengl::texture::basic<Types>::basic(
    sge::opengl::texture::basic_parameters const &_basic_parameters,
    sge::opengl::texture::type const _type,
    parameters_type const &_parameters)
    : Types::base(),
      sge::opengl::texture::base(_type),
      log_{_basic_parameters.log()},
      context_(_basic_parameters.context()),
      resource_flags_(_parameters.resource_flags()),
      capabilities_(_parameters.capabilities()),
      mipmap_(_parameters.mipmap())
{
}

namespace sge::opengl::texture
{
template <typename Types>
basic<Types>::~basic() = default;
}

template <typename Types>
sge::renderer::resource_flags_field sge::opengl::texture::basic<Types>::resource_flags() const
{
  return resource_flags_;
}

template <typename Types>
sge::renderer::texture::capabilities_field sge::opengl::texture::basic<Types>::capabilities() const
{
  return capabilities_;
}

template <typename Types>
sge::renderer::texture::mipmap::object sge::opengl::texture::basic<Types>::mipmap() const
{
  return mipmap_;
}

template <typename Types>
sge::opengl::context::object &sge::opengl::texture::basic<Types>::context() const
{
  return context_.get();
}

template <typename Types>
void sge::opengl::texture::basic<Types>::generate_mipmaps()
{
  sge::opengl::texture::scoped_work_binding const binding(
      log_.get(), context_.get(), this->type(), this->id());

  sge::opengl::texture::mipmap::generate(binding, context_.get(), this->type());
}

#endif
