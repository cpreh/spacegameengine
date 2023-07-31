//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <fcppt/make_ref.hpp>

void sge::font::draw::simple(
    sge::renderer::device::ffp &_renderer,
    sge::renderer::context::ffp &_render_context,
    sge::font::object &_font,
    sge::font::string const &_string,
    sge::font::text_parameters const &_parameters,
    sge::font::vector const &_pos,
    sge::image::color::any::object const &_color,
    sge::renderer::texture::emulate_srgb const _emulate_srgb)
{
  sge::font::draw::static_text const text{
      fcppt::make_ref(_renderer),
      fcppt::make_ref(_font),
      _string,
      _parameters,
      _pos,
      _color,
      _emulate_srgb};

  text.draw(_render_context);
}
