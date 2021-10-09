//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_CLEAR_OPTIONAL_DEPTH_BUFFER_FWD_HPP_INCLUDED
#define SGE_RENDERER_CLEAR_OPTIONAL_DEPTH_BUFFER_FWD_HPP_INCLUDED

#include <sge/renderer/clear/depth_buffer_value.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge::renderer::clear
{

/**
\brief Optional depth buffer clear value

\ingroup sge_renderer
*/
using optional_depth_buffer = fcppt::optional::object<sge::renderer::clear::depth_buffer_value>;

}

#endif
