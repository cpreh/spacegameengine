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


#include <sge/cg/check_state.hpp>
#include <sge/cg/error_listing.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/context/object.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


fcppt::string
sge::cg::error_listing(
	sge::cg::context::object const &_context
)
{
	char const *const ret(
		::cgGetLastListing(
			_context.get()
		)
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGetLastListing failed"),
		sge::cg::exception
	);

	return
		ret
		==
		nullptr
		?
			fcppt::string()
		:
			fcppt::from_std_string(
				ret
			)
		;
}
