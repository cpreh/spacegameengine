//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_POSITION_FWD_HPP_INCLUDED
#define SGE_MODEL_MD3_POSITION_FWD_HPP_INCLUDED

#include <sge/model/md3/scalar.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sge::model::md3
{

using
position
=
fcppt::math::vector::static_<
	sge::model::md3::scalar,
	3
>;

}

#endif
