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
#ifndef SGE_OPENAL_ERROR_HPP_INCLUDED
#define SGE_OPENAL_ERROR_HPP_INCLUDED

#include "openal.hpp"
#include <sge/file.hpp>
#include <sge/string.hpp>
#include <sge/stringize.hpp>

namespace sge
{
namespace openal
{
#define SGE_OPENAL_ERROR_CHECK error_check(SGE_FILE,SGE_STRINGIZE(__LINE__));
#define SGE_ALC_ERROR_CHECK(device) alc_error_check((device),SGE_FILE,SGE_STRINGIZE(__LINE__));
void error_check(string const &,string const &);
void alc_error_check(ALCdevice *,string const &,string const &);
}
}

#endif
