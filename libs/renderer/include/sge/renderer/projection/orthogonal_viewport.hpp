//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PROJECTION_ORTHOGONAL_VIEWPORT_HPP_INCLUDED
#define SGE_RENDERER_PROJECTION_ORTHOGONAL_VIEWPORT_HPP_INCLUDED

#include <sge/renderer/optional_matrix4_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace projection
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::optional_matrix4
orthogonal_viewport(
	sge::renderer::target::viewport const &,
	sge::renderer::projection::near,
	sge::renderer::projection::far
);

}
}
}

#endif
