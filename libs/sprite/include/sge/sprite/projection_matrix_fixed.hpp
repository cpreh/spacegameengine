//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_PROJECTION_MATRIX_FIXED_HPP_INCLUDED
#define SGE_SPRITE_PROJECTION_MATRIX_FIXED_HPP_INCLUDED

#include <sge/sprite/optional_matrix_fwd.hpp>
#include <sge/sprite/projection_dim_fwd.hpp>
#include <sge/sprite/detail/symbol.hpp>


namespace sge::sprite
{

SGE_SPRITE_DETAIL_SYMBOL
sge::sprite::optional_matrix
projection_matrix_fixed(
	sge::sprite::projection_dim const &
);

}

#endif
