//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CONVERT_MIN_FILTER_HPP_INCLUDED
#define SGE_OPENGL_STATE_CONVERT_MIN_FILTER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/min_fwd.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace convert
{

GLenum
min_filter(
	sge::renderer::state::core::sampler::filter::normal::min,
	sge::renderer::state::core::sampler::filter::normal::mip
);

}
}
}
}

#endif
