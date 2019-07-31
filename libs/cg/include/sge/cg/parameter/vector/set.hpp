//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_VECTOR_SET_HPP_INCLUDED
#define SGE_CG_PARAMETER_VECTOR_SET_HPP_INCLUDED

#include <sge/cg/parameter/is_int_float_double.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/check_base_type.hpp>
#include <sge/cg/parameter/vector/detail/check_size.hpp>
#include <sge/cg/parameter/vector/detail/set.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{
namespace vector
{

template<
	typename T,
	fcppt::math::size_type N,
	typename S
>
void
set(
	sge::cg::parameter::object const &_parameter,
	fcppt::math::vector::object<
		T,
		N,
		S
	> const &_vector
)
{
	static_assert(
		sge::cg::parameter::is_int_float_double<
			T
		>::value,
		"T must be int, float or double"
	);

	sge::cg::parameter::vector::detail::check_size(
		_parameter,
		N
	);

	sge::cg::parameter::detail::check_base_type<
		T
	>(
		_parameter
	);

	sge::cg::parameter::vector::detail::set(
		_parameter,
		_vector
	);
}

}
}
}
}

#endif
