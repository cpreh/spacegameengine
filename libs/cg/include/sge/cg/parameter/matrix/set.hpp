//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_MATRIX_SET_HPP_INCLUDED
#define SGE_CG_PARAMETER_MATRIX_SET_HPP_INCLUDED

#include <sge/cg/parameter/is_int_float_double.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/check_base_type.hpp>
#include <sge/cg/parameter/matrix/detail/check_size.hpp>
#include <sge/cg/parameter/matrix/detail/set.hpp>
#include <sge/cg/parameter/matrix/detail/size.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/object_impl.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{
namespace matrix
{

template<
	typename T,
	fcppt::math::size_type R,
	fcppt::math::size_type C,
	typename S
>
void
set(
	sge::cg::parameter::object const &_parameter,
	fcppt::math::matrix::object<
		T,
		R,
		C,
		S
	> const &_matrix
)
{
	static_assert(
		sge::cg::parameter::is_int_float_double<
			T
		>::value,
		"T must be int, float or double"
	);

	sge::cg::parameter::matrix::detail::check_size(
		_parameter,
		sge::cg::parameter::matrix::detail::size(
			R,
			C
		)
	);

	sge::cg::parameter::detail::check_base_type<
		T
	>(
		_parameter
	);

	sge::cg::parameter::matrix::detail::set(
		_parameter,
		_matrix
	);
}

}
}
}
}

#endif
