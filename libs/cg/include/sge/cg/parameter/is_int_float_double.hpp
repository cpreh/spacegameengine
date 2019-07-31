//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_IS_INT_FLOAT_DOUBLE_HPP_INCLUDED
#define SGE_CG_PARAMETER_IS_INT_FLOAT_DOUBLE_HPP_INCLUDED

#include <fcppt/type_traits/is_float_or_double.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/logical/or.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{

template<
	typename Type
>
using
is_int_float_double
=
brigand::or_<
	std::is_same<
		Type,
		int
	>,
	fcppt::type_traits::is_float_or_double<
		Type
	>
>;

}
}
}

#endif
