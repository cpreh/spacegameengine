//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/optional_matrix4.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/target/viewport_is_null.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>


sge::renderer::optional_matrix4
sge::renderer::projection::orthogonal_viewport(
	sge::renderer::target::viewport const &_viewport,
	sge::renderer::projection::near const _near,
	sge::renderer::projection::far const _far
)
{
	return
		sge::renderer::target::viewport_is_null(
			_viewport
		)
		?
			sge::renderer::optional_matrix4()
		:
			sge::renderer::optional_matrix4(
				sge::renderer::projection::orthogonal(
					sge::renderer::projection::rect(
						fcppt::math::vector::null<
							sge::renderer::projection::rect::vector
						>(),
						fcppt::math::dim::structure_cast<
							sge::renderer::projection::rect::dim,
							fcppt::cast::int_to_float_fun
						>(
							_viewport.get().size()
						)
					),
					_near,
					_far
				)
			)
		;
}
