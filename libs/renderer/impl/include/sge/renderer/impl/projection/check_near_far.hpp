//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_IMPL_PROJECTION_CHECK_NEAR_FAR_HPP_INCLUDED
#define SGE_RENDERER_IMPL_PROJECTION_CHECK_NEAR_FAR_HPP_INCLUDED

#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>


namespace sge::renderer::impl::projection
{

void
check_near_far(
	sge::renderer::projection::near,
	sge::renderer::projection::far
);

}

#endif
