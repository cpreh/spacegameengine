//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/exception.hpp>
#include <sge/cg/impl/true.hpp>
#include <sge/cg/impl/parameter/get_type.hpp>
#include <sge/cg/impl/parameter/vector/element_count.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


fcppt::math::size_type
sge::cg::impl::parameter::vector::element_count(
	sge::cg::parameter::object const &_parameter
)
{
	int rows{-1};

	int columns{-1};

	if(
		::cgGetTypeSizes(
			sge::cg::impl::parameter::get_type(
				_parameter
			),
			&rows,
			&columns
		)
		==
		sge::cg::impl::true_
	)
	{
		return
			0;
	}

	if(
		rows
		!=
		1
	)
	{
		throw
			sge::cg::exception{
				FCPPT_TEXT("Unexpected vector row count!")
			};
	}

	return
		fcppt::cast::size<
			fcppt::math::size_type
		>(
			fcppt::cast::to_unsigned(
				columns
			)
		);
}
