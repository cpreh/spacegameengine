//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/projection/far.hpp>
#include <sge/sprite/projection_matrix_far.hpp>


sge::renderer::projection::far
sge::sprite::projection_matrix_far()
{
	return
		sge::renderer::projection::far{
			10.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		};
}
