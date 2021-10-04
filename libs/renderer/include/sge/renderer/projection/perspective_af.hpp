//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PROJECTION_PERSPECTIVE_AF_HPP_INCLUDED
#define SGE_RENDERER_PROJECTION_PERSPECTIVE_AF_HPP_INCLUDED

#include <sge/renderer/matrix4_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/projection/aspect.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>


namespace sge::renderer::projection
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::matrix4
perspective_af(
	sge::renderer::projection::aspect,
	sge::renderer::projection::fov,
	sge::renderer::projection::near,
	sge::renderer::projection::far
);

}

#endif
