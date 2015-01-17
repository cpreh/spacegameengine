/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/cg/parameter/object.hpp>
#include <sge/src/cg/parameter/get_type.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


CGtype
sge::cg::parameter::get_type(
	sge::cg::parameter::object const &_parameter
)
{
	CGtype const ret(
		::cgGetParameterType(
			_parameter.get()
		)
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGetParameterType failed"),
		sge::cg::exception
	);

	FCPPT_ASSERT_THROW(
		ret
		!=
		CG_UNKNOWN_TYPE,
		sge::cg::exception
	);

	return
		ret;
}
