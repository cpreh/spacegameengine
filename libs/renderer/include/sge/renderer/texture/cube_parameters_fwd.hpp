//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_CUBE_PARAMETERS_FWD_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CUBE_PARAMETERS_FWD_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/basic_parameters_fwd.hpp>
#include <sge/renderer/texture/color_format_fwd.hpp>


namespace sge::renderer::texture
{

using
cube_parameters
=
sge::renderer::texture::basic_parameters<
	sge::renderer::size_type,
	sge::renderer::texture::color_format
>;

}

#endif
