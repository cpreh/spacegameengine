//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_SCALAR_SET_HPP_INCLUDED
#define SGE_CG_PARAMETER_SCALAR_SET_HPP_INCLUDED

#include <sge/cg/parameter/is_int_float_double.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/check_type.hpp>
#include <sge/cg/parameter/scalar/detail/set.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{
namespace scalar
{

template<
	typename T
>
void
set(
	sge::cg::parameter::object const &_parameter,
	T const _scalar
)
{
	static_assert(
		sge::cg::parameter::is_int_float_double<
			T
		>::value,
		"T must be int, float or double"
	);

	sge::cg::parameter::detail::check_type<
		T
	>(
		_parameter
	);

	sge::cg::parameter::scalar::detail::set(
		_parameter,
		_scalar
	);
}

}
}
}
}

#endif
