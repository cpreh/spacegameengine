//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_OCCLUSION_QUERY_OPTIONAL_PIXEL_COUNT_FWD_HPP_INCLUDED
#define SGE_RENDERER_OCCLUSION_QUERY_OPTIONAL_PIXEL_COUNT_FWD_HPP_INCLUDED

#include <sge/renderer/occlusion_query/pixel_count.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge::renderer::occlusion_query
{

using optional_pixel_count = fcppt::optional::object<sge::renderer::occlusion_query::pixel_count>;

}

#endif
