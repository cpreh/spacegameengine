/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/cg/parameter/matrix/check_size.hpp>
#include <sge/cg/parameter/matrix/detail/set.hpp>
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
	typename N,
	typename M,
	typename S
>
typename boost::enable_if<
	sge::cg::parameter::is_int_float_double<
		T
	>,
	void
>::type
set(
	sge::cg::parameter::object const &_parameter,
	fcppt::math::matrix::object<
		T,
		N,
		M,
		S
	> const &_matrix
)
{
	sge::cg::parameter::matrix::check_size(
		_parameter,
		_matrix.dimension()
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
