//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/color_format_fwd.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/optional_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <sge/texture/rect_fragmented.hpp>
#include <sge/texture/atlasing/outer_rect.hpp>
#include <sge/texture/atlasing/size.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::texture::rect_fragmented::rect_fragmented(
    sge::renderer::device::core_ref const _renderer,
    sge::renderer::texture::color_format const &_color_format,
    sge::renderer::texture::mipmap::object const &_mipmap,
    sge::renderer::dim2 const &_initial_size)
    : cur_x_(0U),
      cur_y_(0U),
      cur_height_(0U),
      texture_(_renderer.get().create_planar_texture(sge::renderer::texture::planar_parameters(
          _initial_size,
          _color_format,
          _mipmap,
          sge::renderer::resource_flags_field::null(),
          sge::renderer::texture::capabilities_field::null()))),
      texture_count_(0U)
{
}

sge::texture::rect_fragmented::~rect_fragmented() = default;

sge::texture::optional_part_unique_ptr
sge::texture::rect_fragmented::consume_fragment(sge::renderer::dim2 const &_size)
{
  sge::renderer::dim2 const atlased_dim(sge::texture::atlasing::size(_size));

  // if there is no space left for the requested height
  if (cur_y_ + _size.h() >= texture_->size().h())
  {
    return sge::texture::optional_part_unique_ptr();
  }

  // if the current line is full advance to the next
  if (cur_x_ + _size.w() >= texture_->size().w())
  {
    cur_x_ = 0;

    cur_y_ += cur_height_;

    cur_height_ = 0;
  }

  if (cur_y_ + _size.h() >= texture_->size().h())
  {
    return sge::texture::optional_part_unique_ptr();
  }

  sge::texture::part_unique_ptr ret(fcppt::unique_ptr_to_base<sge::texture::part>(
      fcppt::make_unique_ptr<sge::texture::part_fragmented>(
          fcppt::reference_to_base<sge::texture::fragmented>(fcppt::make_ref(*this)),
          sge::texture::atlasing::outer_rect(sge::renderer::lock_rect(
              sge::renderer::lock_rect::vector(cur_x_, cur_y_), atlased_dim)))));

  cur_x_ += _size.w() + 1;

  cur_height_ = std::max(cur_height_, _size.h());

  ++texture_count_;

  return sge::texture::optional_part_unique_ptr(std::move(ret));
}

void sge::texture::rect_fragmented::return_fragment(sge::texture::part const &)
{
  --texture_count_;
}

sge::renderer::texture::planar &sge::texture::rect_fragmented::texture() { return *texture_; }

sge::renderer::texture::planar const &sge::texture::rect_fragmented::texture() const
{
  return *texture_;
}

bool sge::texture::rect_fragmented::repeatable() const { return false; }

bool sge::texture::rect_fragmented::empty() const { return texture_count_ == 0U; }
