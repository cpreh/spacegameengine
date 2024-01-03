//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_BASIC_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASIC_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/basic_parameters_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>

namespace sge::renderer::texture
{

template <typename Dim, typename Format>
class basic_parameters
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  basic_parameters(
      Dim,
      Format const &,
      sge::renderer::texture::mipmap::object const &,
      sge::renderer::resource_flags_field const &,
      sge::renderer::texture::capabilities_field const &);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL Dim const &size() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL Format format() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::texture::mipmap::object const &
  mipmap() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::resource_flags_field const &
  resource_flags() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::texture::capabilities_field const &
  capabilities() const;

private:
  Dim dim_;

  Format format_;

  sge::renderer::texture::mipmap::object mipmap_;

  sge::renderer::resource_flags_field resource_flags_;

  sge::renderer::texture::capabilities_field capabilities_;
};

}

#endif
