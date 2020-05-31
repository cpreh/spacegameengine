//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_COLOR_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_COLOR_FORMAT_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/color_format_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

class color_format
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	color_format(
		sge::image::color::format,
		sge::renderer::texture::emulate_srgb
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::image::color::format
	format() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::texture::emulate_srgb
	emulate_srgb() const;
private:
	sge::image::color::format format_;

	sge::renderer::texture::emulate_srgb emulate_srgb_;
};

}
}
}

#endif
