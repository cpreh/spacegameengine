//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_DRAW_SIMPLE_HPP_INCLUDED
#define SGE_FONT_DRAW_SIMPLE_HPP_INCLUDED

#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/draw/detail/symbol.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>


namespace sge
{
namespace font
{
namespace draw
{

SGE_FONT_DRAW_DETAIL_SYMBOL
void
simple(
	sge::renderer::device::ffp &,
	sge::renderer::context::ffp &,
	sge::font::object &,
	sge::font::string const &,
	sge::font::text_parameters const &,
	sge::font::vector const &,
	sge::image::color::any::object const &,
	sge::renderer::texture::emulate_srgb
);

}
}
}

#endif
