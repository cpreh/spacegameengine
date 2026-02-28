//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_BASIC_BOX_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BOX_HPP_INCLUDED

#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_box_fwd.hpp> // IWYU pragma: keep
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::texture
{

template <typename Types>
// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
class basic_box : public sge::opengl::texture::basic<Types>
{
  using base_type = sge::opengl::texture::basic<Types>;

  FCPPT_NONMOVABLE(basic_box);

public:
  using parameters_type = Types::parameters;

  basic_box(
      sge::opengl::texture::basic_parameters const &,
      sge::opengl::texture::type,
      parameters_type const &,
      sge::opengl::texture::config<Types::buffer_types::dim_types::num_dims> const &);

  ~basic_box() override;

private:
  using nonconst_buffer = base_type::nonconst_buffer;

  using const_buffer = base_type::const_buffer;

  using dim = base_type::dim;
public:
  [[nodiscard]] nonconst_buffer &level(sge::renderer::texture::mipmap::level) override;

  [[nodiscard]] const_buffer const &level(sge::renderer::texture::mipmap::level) const override;

  [[nodiscard]] sge::renderer::texture::mipmap::level_count levels() const override;
private:
  using color_buffer_unique_ptr = fcppt::unique_ptr<nonconst_buffer>;

  using buffer_vector = std::vector<color_buffer_unique_ptr>;

  buffer_vector const levels_;
};

}

#endif
