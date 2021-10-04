//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_MATRIX_DETAIL_SIZE_FWD_HPP_INCLUDED
#define SGE_CG_PARAMETER_MATRIX_DETAIL_SIZE_FWD_HPP_INCLUDED

#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/static_fwd.hpp>


namespace sge::cg::parameter::matrix::detail
{

using
size
=
fcppt::math::dim::static_<
	fcppt::math::size_type,
	2
>;

}

#endif
