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


#include <sge/cg/impl/true.hpp>
#include <sge/cg/impl/parameter/get_type.hpp>
#include <sge/cg/impl/parameter/vector/element_count.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <fcppt/assert/error.hpp>
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
	int
		rows,
		columns;

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
		return
			0;

	FCPPT_ASSERT_ERROR(
		rows
		==
		1
	);

	return
		fcppt::cast::size<
			fcppt::math::size_type
		>(
			fcppt::cast::to_unsigned(
				columns
			)
		);
}
