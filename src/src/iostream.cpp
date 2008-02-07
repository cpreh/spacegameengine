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


#include <iostream>
#include "../iostream.hpp"

#ifndef SGE_NARROW_STRING
sge::istream& sge::cin(std::wcin);
sge::ostream& sge::cout(std::wcout);
sge::ostream& sge::cerr(std::wcerr);
sge::ostream& sge::clog(std::wclog);
#else
sge::istream& sge::cin(std::cin);
sge::ostream& sge::cout(std::cout);
sge::ostream& sge::cerr(std::cerr);
sge::ostream& sge::clog(std::clog);
#endif
