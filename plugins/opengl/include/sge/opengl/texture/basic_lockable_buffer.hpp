//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_BASIC_LOCKABLE_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_LOCKABLE_BUFFER_HPP_INCLUDED

#include <sge/image/pitch_fwd.hpp>
#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/texture/basic_buffer.hpp>
#include <sge/opengl/texture/basic_buffer_parameters_fwd.hpp>
#include <sge/opengl/texture/basic_fwd.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <sge/opengl/texture/lock_base.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_decl.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/math/box/object_decl.hpp>
#include <fcppt/optional/object_decl.hpp>

namespace sge::opengl::texture
{

template <typename Types>
class basic_lockable_buffer : public sge::opengl::texture::basic_buffer<Types>
{
  FCPPT_NONMOVABLE(basic_lockable_buffer);

public:
  using gl_base = sge::opengl::texture::basic_buffer<Types>;

  using image_tag = typename gl_base::image_tag;

  using color_tag = typename gl_base::color_tag;

  using format_type = typename gl_base::format_type;

  using dim = typename gl_base::dim;

  using config_type = sge::opengl::texture::config<dim::static_size::value>;

  using const_config_ref = fcppt::reference<config_type const>;

  basic_lockable_buffer(
      format_type, const_config_ref, sge::opengl::texture::basic_buffer_parameters const &);

  ~basic_lockable_buffer() override;

  using pointer = sge::opengl::texture::lock_base::pointer;

  using const_pointer = sge::opengl::texture::lock_base::const_pointer;

  using base_type = typename gl_base::base_type;

  using lock_area = typename base_type::lock_area;

  using view = typename base_type::view;

  using const_view = typename base_type::const_view;

private:
  view lock(lock_area const &, sge::renderer::lock_mode) override;

  const_view lock_c(lock_area const &) const override;

  void unlock() const override;

  void lock_me(lock_area const &, sge::renderer::lock_flags::method) const;

  view lock_view();

  const_view lock_view() const;

  dim lock_dim() const;

  fcppt::log::object_reference const log_;

  sge::opengl::context::object_ref const context_;

  const_config_ref const config_;

  sge::opengl::texture::type const type_;

  sge::renderer::resource_flags_field const resource_flags_;

  sge::opengl::color_order const color_order_;

  sge::opengl::color_base_type const color_base_type_;

  sge::opengl::internal_color_format const internal_color_format_;

  sge::renderer::size_type const stride_;

  using lock_unique_ptr = fcppt::unique_ptr<sge::opengl::texture::lock_base>;

  using optional_lock_unique_ptr = fcppt::optional::object<lock_unique_ptr>;

  mutable optional_lock_unique_ptr lock_;

  using optional_lock_area = fcppt::optional::object<lock_area>;

  mutable optional_lock_area lock_area_;

  using pitch = sge::image::pitch<image_tag>;
};

}

#endif
