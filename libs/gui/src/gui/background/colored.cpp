//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/background/base.hpp>
#include <sge/gui/background/colored.hpp>
#include <sge/gui/main_area/reference.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>

sge::gui::background::colored::colored(sge::gui::main_area::reference const _main_area)
    : sge::gui::background::base(_main_area)
{
}

sge::gui::background::colored::~colored() = default;

void sge::gui::background::colored::on_draw(
    sge::gui::renderer::base &_renderer,
    sge::renderer::context::ffp &_context,
    sge::rucksack::rect const &_area)
{
  constexpr double const color{0.75};

  constexpr double const alpha{0.25};

  _renderer.fill_rect(
      _context,
      _area,
      sge::image::color::any::object(sge::image::color::rgba8((
          sge::image::color::init::red() %= color)(sge::image::color::init::green() %= color)(
          sge::image::color::init::blue() %= color)(sge::image::color::init::alpha() %= alpha))));
}
