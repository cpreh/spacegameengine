//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_DEPTH_STENCIL_PARAMETERS_FWD_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_DEPTH_STENCIL_PARAMETERS_FWD_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/texture/basic_parameters_fwd.hpp>


namespace sge::renderer::texture
{

using
depth_stencil_parameters
=
sge::renderer::texture::basic_parameters<
	sge::renderer::dim2,
	sge::image::ds::format
>;

}

#endif
