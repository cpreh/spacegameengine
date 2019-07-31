//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/ds/format.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/impl/texture/instantiate_basic_parameters.hpp>
#include <sge/renderer/texture/depth_stencil_parameters.hpp>


SGE_RENDERER_IMPL_TEXTURE_INSTANTIATE_BASIC_PARAMETERS(
	sge::renderer::dim2,
	sge::image::ds::format
);
