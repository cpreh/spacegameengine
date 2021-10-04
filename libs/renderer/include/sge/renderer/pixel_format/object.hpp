//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PIXEL_FORMAT_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_FORMAT_OBJECT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>


namespace sge::renderer::pixel_format
{

/**
\brief Describes a pixel format

This class contains all the necessary information to create a pixel format,
which consists of a bit depth for the color buffer, depth or stencil buffers,
optional multi samples, and if srgb conversion should be done.
*/
class object
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	object(
		sge::renderer::pixel_format::color,
		sge::renderer::pixel_format::depth_stencil,
		sge::renderer::pixel_format::optional_multi_samples const &,
		sge::renderer::pixel_format::srgb
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::pixel_format::color
	color() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::pixel_format::depth_stencil
	depth_stencil() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::pixel_format::optional_multi_samples
	multi_samples() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::pixel_format::srgb
	srgb() const;
private:
	sge::renderer::pixel_format::color color_;

	sge::renderer::pixel_format::depth_stencil depth_stencil_;

	sge::renderer::pixel_format::optional_multi_samples multi_samples_;

	sge::renderer::pixel_format::srgb srgb_;
};

}

#endif
