//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/impl/parameter/get_type.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/matrix/detail/check_size.hpp>
#include <sge/cg/parameter/matrix/detail/size.hpp>
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
		sge::cg::impl::parameter::get_type(
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
