//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_IMPL_TEXTURE_HPP_INCLUDED
#define SGE_CEGUI_IMPL_TEXTURE_HPP_INCLUDED

#include <sge/cegui/impl/texture_fwd.hpp>
#include <sge/cegui/impl/texture_parameters.hpp>
#include <sge/cegui/impl/fwds/rectf_fwd.hpp>
#include <sge/cegui/impl/fwds/sizef_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/texture/capabilities_field_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/optional/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Size.h>
#include <CEGUI/Texture.h>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>

namespace CEGUI
{
class String;
}

namespace sge::cegui::impl
{

class texture : public CEGUI::Texture
{
  FCPPT_NONMOVABLE(texture);

public:
  // Constructs a texture that will be loaded later by calling
  // loadFromFile or create_from_view. It won't have a valid size or
  // texture object until then.
  texture(
      fcppt::log::object &, // NOLINT(google-runtime-references)
      sge::cegui::impl::texture_parameters const &,
      CEGUI::String const &name);

  // Constructs a texture with a given size, but undefined contents.
  // This texture might be rendered to or it might get data by
  // loadFromMemory.
  texture(
      fcppt::log::object &, // NOLINT(google-runtime-references)
      sge::cegui::impl::texture_parameters const &,
      CEGUI::String const &name,
      CEGUI::Sizef const &,
      sge::renderer::texture::capabilities_field const &);

  ~texture() override;

  using optional_planar_texture_ref = fcppt::optional::reference<sge::renderer::texture::planar>;

  [[nodiscard]] optional_planar_texture_ref impl();

  // This is called by the image_codec to circumvent the
  // loadFromMemory mechanism
  void create_from_view(sge::image2d::view::const_object const &);

private:
  [[nodiscard]] CEGUI::String const &getName() const override;

  [[nodiscard]] CEGUI::Sizef const &getSize() const override;

  [[nodiscard]] CEGUI::Sizef const &getOriginalDataSize() const override;

  [[nodiscard]] CEGUI::Vector2f const &getTexelScaling() const override;

public:
  void loadFromFile(CEGUI::String const &filename, CEGUI::String const &resourceGroup) override;

private:
  void loadFromMemory(
      void const *buffer, CEGUI::Sizef const &buffer_size, CEGUI::Texture::PixelFormat) override;

  void blitFromMemory(void const *sourceData, CEGUI::Rectf const &) override;

  void blitToMemory(void *) override;

  [[nodiscard]] bool isPixelFormatSupported(CEGUI::Texture::PixelFormat) const override;

  using optional_sizef = fcppt::optional::object<CEGUI::Sizef>;

  using optional_vector2f = fcppt::optional::object<CEGUI::Vector2f>;

  FCPPT_DECLARE_STRONG_TYPEDEF(optional_vector2f, optional_texel_scaling);

  using optional_planar_unique_ptr =
      fcppt::optional::object<sge::renderer::texture::planar_unique_ptr>;

  texture(
      fcppt::log::object &, // NOLINT(google-runtime-references)
      sge::cegui::impl::texture_parameters,
      CEGUI::String const &,
      sge::cegui::impl::texture::optional_sizef,
      sge::cegui::impl::texture::optional_texel_scaling,
      sge::cegui::impl::texture::optional_planar_unique_ptr &&);

  fcppt::log::object log_;

  sge::cegui::impl::texture_parameters const texture_parameters_;

  CEGUI::String const name_;

  // We _have_ to cache this because getSize returns a reference
  sge::cegui::impl::texture::optional_sizef size_;

  sge::cegui::impl::texture::optional_texel_scaling texel_scaling_;

  optional_planar_unique_ptr texture_;
};

}

#endif
