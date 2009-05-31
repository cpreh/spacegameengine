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


#ifndef SGE_ERROR_CHECK_STATE_HPP_INCLUDED
#define SGE_ERROR_CHECK_STATE_HPP_INCLUDED

#include <sge/format.hpp>
#include <sge/text.hpp>
#include <sge/file.hpp>
#include <sge/string.hpp>
#include <sge/stringize.hpp>

#define SGE_ERROR_CHECK_STATE(\
	exception,\
	message,\
	error_type,\
	function,\
	success_code, \
	error_code_function \
) \
{ \
	error_type const sge_return_value_(\
		function \
	); \
	\
	if(sge_return_value_ != success_code)\
		throw exception(\
			sge::str( \
				sge::format(\
					SGE_TEXT("Function failed in %1%:%2% (errorcode: %3%): %4%")\
				) \
				% SGE_FILE \
				% SGE_STRINGIZE(__LINE__) \
				% error_code_function(sge_return_value_) \
				% message \
			) \
		);\
} \

#endif
