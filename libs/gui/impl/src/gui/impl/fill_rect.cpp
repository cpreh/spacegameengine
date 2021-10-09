//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/impl/draw_sprite.hpp>
#include <sge/gui/impl/fill_rect.hpp>
#include <sge/gui/impl/sprite_type_choices.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <fcppt/mpl/list/object.hpp>

void sge::gui::impl::fill_rect(
    sge::renderer::device::core &_renderer,
    sge::renderer::context::ffp &_context,
    sge::rucksack::rect const &_rect,
    sge::image::color::any::object const &_color)
{
  {
    sge::rucksack::dim const size(_rect.size());

    if (size.w() <= -0 || size.h() <= 0)
    {
      return;
    }
  }

  using color_format = sge::image::color::rgba8_format;

  using choices = sge::sprite::config::choices<
      sge::gui::impl::sprite_type_choices,
      sge::sprite::config::pos<sge::sprite::config::pos_option::pos>,
      sge::sprite::config::normal_size<sge::sprite::config::texture_size_option::never>,
      fcppt::mpl::list::object<sge::sprite::config::with_color<color_format>>>;

  sge::gui::impl::draw_sprite(
      _renderer,
      _context,
      sge::sprite::object<choices>(
          sge::sprite::roles::pos{} = _rect.pos(),
          sge::sprite::roles::size{} = _rect.size(),
          sge::sprite::roles::color{} = sge::image::color::any::convert<color_format>(_color)));
}
