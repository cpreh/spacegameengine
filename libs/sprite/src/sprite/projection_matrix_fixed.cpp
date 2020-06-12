//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/projection/dim.hpp>
#include <sge/renderer/projection/orthogonal_wh.hpp>
#include <sge/sprite/optional_matrix.hpp>
#include <sge/sprite/projection_dim.hpp>
#include <sge/sprite/projection_matrix_far.hpp>
#include <sge/sprite/projection_matrix_fixed.hpp>
#include <sge/sprite/projection_matrix_near.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::sprite::optional_matrix
sge::sprite::projection_matrix_fixed(
	sge::sprite::projection_dim const &_size
)
{
	return
		fcppt::math::dim::contents(
			_size.get()
		)
		!=
		0U
		?
			sge::sprite::optional_matrix(
				sge::renderer::projection::orthogonal_wh(
					fcppt::math::dim::structure_cast<
						sge::renderer::projection::dim,
						fcppt::cast::int_to_float_fun
					>(
						_size.get()
					),
					sge::sprite::projection_matrix_near(),
					sge::sprite::projection_matrix_far()
				)
			)
		:
			sge::sprite::optional_matrix()
		;
}
