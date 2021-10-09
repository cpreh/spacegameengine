//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_TEXTURE_BASIC_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/base.hpp>
#include <sge/d3d9/texture/basic_buffer_fwd.hpp>
#include <sge/d3d9/texture/basic_fwd.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>

namespace sge
{
namespace d3d9
{
namespace texture
{

template <typename Types>
class basic : public Types::base, public sge::d3d9::texture::base, public sge::d3d9::resource
{
  FCPPT_NONCOPYABLE(basic);

public:
  typedef typename Types::base base;

  typedef typename Types::parameters parameters_type;

  typedef typename Types::d3d_type d3d_type;

  typedef sge::d3d9::texture::basic_buffer<Types> buffer_type;

  basic(IDirect3DDevice9 &, parameters_type const &);

  ~basic() override;

protected:
  sge::renderer::resource_flags_field resource_flags() const override;

private:
  sge::renderer::texture::capabilities_field capabilities() const override;

  sge::renderer::texture::mipmap::object mipmap() const override;

  void generate_mipmaps() override;

protected:
  sge::renderer::texture::mipmap::level_count levels() const override;

public:
  d3d_type &get() const override;

  sge::image::color::format color_format() const override;

protected:
  parameters_type const &parameters() const;

private:
  typedef typename Types::unique_ptr d3d_unique_ptr;

  d3d_unique_ptr create(D3DPOOL, sge::d3d9::usage) const;

  void init();

  void on_reset() override;

  void on_loss() override;

  IDirect3DDevice9 &device_;

  parameters_type const parameters_;

  sge::image::color::format const color_format_;

  D3DFORMAT const d3d_color_format_;

  sge::d3d9::usage const usage_;

  typedef fcppt::optional::object<d3d_unique_ptr> optional_d3d_unique_ptr;

  optional_d3d_unique_ptr texture_;
};

}
}
}

#endif
