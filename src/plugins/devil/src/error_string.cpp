/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../error_string.hpp"
#include <fcppt/assert.hpp>
#include <fcppt/from_std_string.hpp>
#include <IL/il.h>
#include <IL/ilu.h>

fcppt::string const
sge::devil::error_string(
	ILenum const _error
)
{
	FCPPT_ASSERT(
		_error != IL_NO_ERROR
	);

	ILconst_string const ret(
		::iluErrorString(
			_error
		)
	);

	return
#ifdef UNICODE
		ret
#else
		fcppt::from_std_string(
			ret
		);
#endif
}
