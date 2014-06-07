/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/src/cg/true.hpp>
#include <sge/src/cg/parameter/get_type.hpp>
#include <sge/src/cg/parameter/vector/element_count.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


fcppt::math::size_type
sge::cg::parameter::vector::element_count(
	sge::cg::parameter::object const &_parameter
)
{
	int
		rows,
		columns;

	if(
		::cgGetTypeSizes(
			sge::cg::parameter::get_type(
				_parameter
			),
			&rows,
			&columns
		)
		==
		sge::cg::true_
	)
		return 0;

	FCPPT_ASSERT_ERROR(
		rows
		==
		1
	);

	return
		static_cast<
			fcppt::math::size_type
		>(
			columns
		);
}
