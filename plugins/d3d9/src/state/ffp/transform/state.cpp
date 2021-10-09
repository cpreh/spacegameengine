//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/transform/state.hpp>

sge::d3d9::state::ffp::transform::state::state(D3DMATRIX const &_matrix) : matrix_(_matrix) {}

D3DMATRIX const &sge::d3d9::state::ffp::transform::state::matrix() const { return matrix_; }
