/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_RENDERER_PIXEL_FORMAT_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_FORMAT_OBJECT_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>


namespace sge
{
namespace renderer
{
namespace pixel_format
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
	SGE_RENDERER_SYMBOL
	object(
		sge::renderer::pixel_format::color::type,
		sge::renderer::pixel_format::depth_stencil::type,
		sge::renderer::pixel_format::optional_multi_samples const &,
		sge::renderer::pixel_format::srgb::type
	);

	SGE_RENDERER_SYMBOL
	sge::renderer::pixel_format::color::type
	color() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::pixel_format::depth_stencil::type
	depth_stencil() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::pixel_format::optional_multi_samples const
	multi_samples() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::pixel_format::srgb::type
	srgb() const;
private:
	sge::renderer::pixel_format::color::type color_;

	sge::renderer::pixel_format::depth_stencil::type depth_stencil_;

	sge::renderer::pixel_format::optional_multi_samples multi_samples_;

	sge::renderer::pixel_format::srgb::type srgb_;
};

}
}
}

#endif
