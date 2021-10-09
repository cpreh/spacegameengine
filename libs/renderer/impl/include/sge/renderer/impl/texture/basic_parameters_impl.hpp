//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_TEXTURE_BASIC_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_TEXTURE_BASIC_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/basic_parameters.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Dim, typename Format>
sge::renderer::texture::basic_parameters<Dim, Format>::basic_parameters(
    Dim _dim,
    Format const &_format,
    sge::renderer::texture::mipmap::object const &_mipmap,
    sge::renderer::resource_flags_field const &_resource_flags,
    sge::renderer::texture::capabilities_field const &_capabilities)
    : dim_(std::move(_dim)),
      format_(_format),
      mipmap_(_mipmap),
      resource_flags_(_resource_flags),
      capabilities_(_capabilities)
{
}

template <typename Dim, typename Format>
Dim const &sge::renderer::texture::basic_parameters<Dim, Format>::size() const
{
  return dim_;
}

template <typename Dim, typename Format>
Format sge::renderer::texture::basic_parameters<Dim, Format>::format() const
{
  return format_;
}

template <typename Dim, typename Format>
sge::renderer::texture::mipmap::object const &
sge::renderer::texture::basic_parameters<Dim, Format>::mipmap() const
{
  return mipmap_;
}

template <typename Dim, typename Format>
sge::renderer::resource_flags_field const &
sge::renderer::texture::basic_parameters<Dim, Format>::resource_flags() const
{
  return resource_flags_;
}

template <typename Dim, typename Format>
sge::renderer::texture::capabilities_field const &
sge::renderer::texture::basic_parameters<Dim, Format>::capabilities() const
{
  return capabilities_;
}

#endif
