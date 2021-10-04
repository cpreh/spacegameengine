//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_VECTOR_FWD_HPP_INCLUDED
#define SGE_RUCKSACK_VECTOR_FWD_HPP_INCLUDED

#include <sge/rucksack/dim_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sge::rucksack
{

using
vector
=
fcppt::math::vector::static_<
	sge::rucksack::scalar,
	sge::rucksack::dim_size::value
>;

}

#endif
