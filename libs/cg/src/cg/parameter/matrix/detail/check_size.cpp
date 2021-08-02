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
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


namespace
{

using
cg_size
=
fcppt::math::dim::static_<
	int,
	2
>;

cg_size
get_size(
	CGtype const _type
)
{
	int rows{-1};

	int columns{-1};

	::cgGetMatrixSize(
		_type,
		&rows,
		&columns
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGetMatrixSize failed"),
		sge::cg::exception
	)

	return
		cg_size{
			rows,
			columns
		};
}

}

void
sge::cg::parameter::matrix::detail::check_size(
	sge::cg::parameter::object const &_parameter,
	sge::cg::parameter::matrix::detail::size const &_dim
)
{
	cg_size const result{
		get_size(
			sge::cg::impl::parameter::get_type(
				_parameter
			)
		)
	};

	if(
		fcppt::math::dim::contents(
			result
		)
		==
		0
	)
	{
		throw
			sge::cg::exception{
				FCPPT_TEXT("Parameter is not a matrix")
			};
	}

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

	if(
		_dim
		!=
		unsigned_result
	)
	{
		throw
			sge::cg::exception{
				FCPPT_TEXT("Unexpected matrix size!")
			};
	}
}
