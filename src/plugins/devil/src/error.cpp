/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <IL/il.h>
#include <IL/ilu.h>
#include "../error.hpp"
#include <fcppt/string.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <sge/iconv.hpp>

void sge::devil::check_errors()
{
	ILenum e = ilGetError();
	if(e == IL_NO_ERROR)
		return;

	string error_message(FCPPT_TEXT("The following devil errors were detected:\n"));
	do
	{
		error_message +=
#ifdef UNICODE
			iluErrorString(e);
#else
			iconv(iluErrorString(e));
#endif
		error_message += FCPPT_TEXT('\n');
	}
	while((e = ilGetError()) != IL_NO_ERROR);
	throw exception(error_message);
}
