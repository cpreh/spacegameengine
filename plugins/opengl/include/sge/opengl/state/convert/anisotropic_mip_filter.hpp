//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CONVERT_ANISOTROPIC_MIP_FILTER_HPP_INCLUDED
#define SGE_OPENGL_STATE_CONVERT_ANISOTROPIC_MIP_FILTER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/mip_fwd.hpp>


namespace sge::opengl::state::convert
{

GLenum
anisotropic_mip_filter(
	sge::renderer::state::core::sampler::filter::anisotropic::mip
);

}

#endif
