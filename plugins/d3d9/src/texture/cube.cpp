//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/texture/basic_buffer.hpp>
#include <sge/d3d9/texture/basic_impl.hpp>
#include <sge/d3d9/texture/cube.hpp>
#include <sge/d3d9/texture/cube_buffer.hpp>
#include <sge/d3d9/texture/cube_types.hpp>
#include <sge/d3d9/texturefuncs/get_cube_map_surface.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/color_buffer/writable_surface.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/enum/array_impl.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::d3d9::texture::cube::cube(
    IDirect3DDevice9 &_device, sge::renderer::texture::cube_parameters const &_params)
    : sge::d3d9::texture::cube_basic(_device, _params),
      sides_(fcppt::enum_::array_init<side_array>(
          [this](sge::renderer::texture::cube_side const _side)
          {
            return fcppt::algorithm::map<level_vector>(
                fcppt::make_int_range_count(
                    sge::renderer::texture::mipmap::level(this->levels().get())),
                [this, _side](sge::renderer::texture::mipmap::level const _index)
                {
                  return fcppt::unique_ptr_to_base<sge::renderer::texture::cube::nonconst_buffer>(
                      fcppt::make_unique_ptr<sge::d3d9::texture::cube_buffer>(
                          sge::d3d9::texture::cube_buffer::d3d_buffer_create_function(
                              std::bind(&sge::d3d9::texture::cube::get_level, this, _side, _index)),
                          this->color_format(),
                          this->resource_flags()));
                });
          }))
{
}

FCPPT_PP_POP_WARNING

sge::d3d9::texture::cube::~cube() {}

sge::renderer::size_type sge::d3d9::texture::cube::border_size() const
{
  return this->parameters().size();
}

sge::renderer::texture::cube::nonconst_buffer &sge::d3d9::texture::cube::level(
    sge::renderer::texture::cube_side const _side,
    sge::renderer::texture::mipmap::level const _level)
{
  return *sides_[_side][_level.get()];
}

sge::renderer::texture::cube::const_buffer const &sge::d3d9::texture::cube::level(
    sge::renderer::texture::cube_side const _side,
    sge::renderer::texture::mipmap::level const _level) const
{
  return *sides_[_side][_level.get()];
}

sge::d3d9::surface::d3d_unique_ptr sge::d3d9::texture::cube::get_level(
    sge::renderer::texture::cube_side const _side,
    sge::renderer::texture::mipmap::level const _level)
{
  return sge::d3d9::texturefuncs::get_cube_map_surface(this->get(), _side, _level);
}

template class sge::d3d9::texture::basic<sge::d3d9::texture::cube_types>;
