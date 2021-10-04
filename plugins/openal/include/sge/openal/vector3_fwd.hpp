//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_VECTOR3_FWD_HPP_INCLUDED
#define SGE_OPENAL_VECTOR3_FWD_HPP_INCLUDED

#include <sge/openal/al.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sge::openal
{

using
vector3
=
fcppt::math::vector::static_<
	ALfloat,
	3
>;

}

#endif
