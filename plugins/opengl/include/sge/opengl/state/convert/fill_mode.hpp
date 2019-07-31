//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CONVERT_FILL_MODE_HPP_INCLUDED
#define SGE_OPENGL_STATE_CONVERT_FILL_MODE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace convert
{

GLenum
fill_mode(
	sge::renderer::state::core::rasterizer::fill_mode
);

}
}
}
}

#endif
