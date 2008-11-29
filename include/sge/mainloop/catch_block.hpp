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


#ifndef SGE_MAINLOOP_CATCH_BLOCK_HPP_INCLUDED
#define SGE_MAINLOOP_CATCH_BLOCK_HPP_INCLUDED

#include "../exception.hpp"
#include "../text.hpp"
#include "../iostream.hpp"
#include "../exception.hpp"
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

#define SGE_MAINLOOP_CATCH_BLOCK \
catch(sge::exception const &e)\
{\
	sge::cerr << e.what() << SGE_TEXT('\n');\
	return EXIT_FAILURE;\
}\
catch(std::exception const &e)\
{\
	std::cerr << e.what() << '\n';\
	return EXIT_FAILURE;\
}\
catch(...)\
{\
	sge::cerr << SGE_TEXT("Unknown exception.\n");\
	return EXIT_FAILURE;\
}

#endif
