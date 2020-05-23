//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_PARAMETERS_HPP_INCLUDED

#include <sge/image/ds/format.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>


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
		sge::renderer::dim2,
		sge::image::ds::format
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::dim2 const &
	size() const;

	[[nodiscard]]
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
