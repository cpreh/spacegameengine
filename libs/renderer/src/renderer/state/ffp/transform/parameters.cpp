//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>


sge::renderer::state::ffp::transform::parameters::parameters(
	sge::renderer::matrix4 const &_matrix
)
:
	matrix_(
		_matrix
	)
{
}

sge::renderer::matrix4 const &
sge::renderer::state::ffp::transform::parameters::matrix() const
{
	return
		matrix_;
}
