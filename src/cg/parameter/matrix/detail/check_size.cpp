/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/matrix/detail/check_size.hpp>
#include <sge/src/cg/parameter/get_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/matrix/dim_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


void
sge::cg::parameter::matrix::detail::check_size(
	sge::cg::parameter::object const &_parameter,
	fcppt::math::matrix::dim_type const &_dim
)
{
	int
		rows,
		columns;

	::cgGetMatrixSize(
		sge::cg::parameter::get_type(
			_parameter
		),
		&rows,
		&columns
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGetMatrixSize failed"),
		sge::cg::exception
	)

	FCPPT_ASSERT_ERROR_MESSAGE(
		rows
		!=
		0
		&&
		columns
		!=
		0,
		FCPPT_TEXT("Parameter is not a matrix")
	);

	FCPPT_ASSERT_ERROR(
		static_cast<
			fcppt::math::matrix::dim_type::value_type
		>(
			rows
		)
		==
		_dim.w()
		&&
		static_cast<
			fcppt::math::matrix::dim_type::value_type
		>(
			columns
		)
		==
		_dim.h()
	);
}
