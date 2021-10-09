//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/impl/draw_image.hpp>
#include <sge/gui/impl/draw_sprite.hpp>
#include <sge/gui/impl/image_sprite_choices.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>

void sge::gui::impl::draw_image(
    sge::renderer::device::core &_renderer,
    sge::renderer::context::ffp &_context,
    sge::texture::part const &_texture,
    sge::rucksack::vector const &_pos)
{
  sge::gui::impl::draw_sprite(
      _renderer,
      _context,
      sge::sprite::object<sge::gui::impl::image_sprite_choices<
          sge::sprite::config::texture_coordinates::automatic,
          sge::sprite::config::texture_size_option::always>>(
          sge::sprite::roles::pos{} = _pos,
          sge::sprite::roles::texture0{} = sge::texture::const_part_ref(_texture)));
}
