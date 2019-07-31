//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/sprite/optional_matrix.hpp>
#include <sge/sprite/projection_matrix.hpp>


sge::sprite::optional_matrix
sge::sprite::projection_matrix(
	sge::renderer::target::viewport const &_viewport
)
{
	return
		sge::renderer::projection::orthogonal_viewport(
			_viewport,
			// TODO
			sge::renderer::projection::near{
				0.f
			},
			sge::renderer::projection::far{
				10.f
			}
		);
}
