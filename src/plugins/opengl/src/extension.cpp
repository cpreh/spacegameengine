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


#include <sge/config.h>
#include "../extension.hpp"

sge::string sge::ogl::extension_not_supported_string(const string& extension)
{
	return string(SGE_TEXT("The following opengl extension which is needed by some classes of the opengl plugin is not supported!: '"))
               + extension
	       + SGE_TEXT("'.")
#ifdef SGE_LINUX_PLATFORM
               + SGE_TEXT(" Your current X system has to support direct rendering. Please examine \"glxinfo | grep rendering\" and see if it is set to 'Yes'."
                 " If that's not the case, install a graphics driver that is capable of direct rendering. If it still doesn't work, maybe your hardware"
                 " doesn't support the extension (though unlikely).")
#elif SGE_WINDOWS_PLATFORM
               + SGE_TEXT(" Please make sure you installed the latest graphics driver for Windows.")
#endif
	;
}
