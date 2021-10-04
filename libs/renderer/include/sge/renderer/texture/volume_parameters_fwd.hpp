//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_VOLUME_PARAMETERS_FWD_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_VOLUME_PARAMETERS_FWD_HPP_INCLUDED

#include <sge/renderer/dim3_fwd.hpp>
#include <sge/renderer/texture/basic_parameters_fwd.hpp>
#include <sge/renderer/texture/color_format_fwd.hpp>


namespace sge::renderer::texture
{

using
volume_parameters
=
sge::renderer::texture::basic_parameters<
	sge::renderer::dim3,
	sge::renderer::texture::color_format
>;

}

#endif
