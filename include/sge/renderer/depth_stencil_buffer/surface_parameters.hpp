/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_PARAMETERS_HPP_INCLUDED

#include <sge/image/ds/format.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace depth_stencil_buffer
{

class surface_parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	surface_parameters(
		sge::renderer::dim2 const &,
		sge::image::ds::format
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::dim2 const &
	size() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::image::ds::format
	format() const;
private:
	sge::renderer::dim2 size_;

	sge::image::ds::format format_;
};

}
}
}

#endif
