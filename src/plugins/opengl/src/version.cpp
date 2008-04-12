/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../version.hpp"
#include <sge/exception.hpp>

sge::string sge::ogl::version_not_supported_string(const string& function, const string& min_version)
{
	return SGE_TEXT("Your opengl version does not implement the following function: \"")
	     + function
	     + SGE_TEXT("\". The minimal opengl version must be ")
	     + min_version
	     + SGE_TEXT("! Please make sure you run the latest driver for your video hardware.");
}

void sge::ogl::on_not_supported(const string& function,
                                const string& min_version,
                                const string& possible_extensions)
{
	throw exception(SGE_TEXT("You tried to use the following functionality: \"")
	               + function
	               + SGE_TEXT("\" which is not supported by your implementation. opengl-")
	               + min_version
	               + SGE_TEXT(" is at least required. The possible extensions sge can use are: \"")
	               + possible_extensions
	               + SGE_TEXT("\"."));
}
