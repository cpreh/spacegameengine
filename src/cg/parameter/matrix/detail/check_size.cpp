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


#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/matrix/detail/check_size.hpp>
#include <sge/cg/parameter/matrix/detail/size.hpp>
#include <sge/src/cg/parameter/get_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


void
sge::cg::parameter::matrix::detail::check_size(
	sge::cg::parameter::object const &_parameter,
	sge::cg::parameter::matrix::detail::size const _dim
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

	fcppt::math::dim::static_<
		int,
		2
	> const result(
		rows,
		columns
	);

	FCPPT_ASSERT_ERROR_MESSAGE(
		fcppt::math::dim::contents(
			result
		)
		!=
		0,
		FCPPT_TEXT("Parameter is not a matrix")
	);

	auto const unsigned_result(
		fcppt::math::dim::structure_cast<
			sge::cg::parameter::matrix::detail::size,
			fcppt::cast::size_fun
		>(
			fcppt::math::dim::to_unsigned(
				result
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		_dim
		==
		unsigned_result
	);
}
