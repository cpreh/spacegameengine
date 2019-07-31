//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_PROJECTION_MATRIX_HPP_INCLUDED
#define SGE_SPRITE_PROJECTION_MATRIX_HPP_INCLUDED

#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/sprite/optional_matrix_fwd.hpp>
#include <sge/sprite/detail/symbol.hpp>


namespace sge
{
namespace sprite
{

SGE_SPRITE_DETAIL_SYMBOL
sge::sprite::optional_matrix
projection_matrix(
	sge::renderer::target::viewport const &
);

}
}

#endif
