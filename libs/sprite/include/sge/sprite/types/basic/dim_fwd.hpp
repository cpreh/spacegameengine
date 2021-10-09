//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_TYPES_BASIC_DIM_FWD_HPP_INCLUDED
#define SGE_SPRITE_TYPES_BASIC_DIM_FWD_HPP_INCLUDED

#include <fcppt/math/dim/static_fwd.hpp>

namespace sge::sprite::types::basic
{

template <typename Type>
using dim = fcppt::math::dim::static_<Type, 2>;

}

#endif
