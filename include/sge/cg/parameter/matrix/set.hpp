/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


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
typename
boost::enable_if<
	sge::cg::parameter::is_int_float_double<
		T
	>,
	void
>::type
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
