//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_IMPL_TYPE_INTEGRAL_C_HPP_INCLUDED
#define SGE_CG_IMPL_TYPE_INTEGRAL_C_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::cg::impl
{

template<
	CGtype Type
>
using
type_integral_c
=
std::integral_constant<
	CGtype,
	Type
>;

}

#endif
