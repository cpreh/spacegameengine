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


#ifndef SGE_ERROR_STATE_SENTRY_HPP_INCLUDED
#define SGE_ERROR_STATE_SENTRY_HPP_INCLUDED

#include <sge/format.hpp>
#include <sge/text.hpp>
#include <sge/file.hpp>
#include <sge/string.hpp>
#include <sge/stringize.hpp>
#include <sge/noncopyable.hpp>
#include <exception>

#define SGE_ERROR_STATE_SENTRY(\
	exception,\
	message,\
	error_type,\
	function,\
	success_code, \
	error_code_function \
) \
class sge_error_sentry_ { \
	SGE_NONCOPYABLE(sge_error_sentry_) \
\
	sge::string const message_str; \
\
public: \
	explicit sge_error_sentry_( \
		sge::string const & message_str) \
	: \
		message_str(message_str) \
	{} \
	\
	~sge_error_sentry_() \
	{ \
		if(std::uncaught_exception())\
			return;\
		\
		error_type const ret(\
			function() \
		); \
		\
		if(ret != success_code)\
			throw exception(\
				sge::str( \
					sge::format(\
						SGE_TEXT("Function failed in %1%:%2% (errorcode: %3%): %4%")\
					) \
					% SGE_FILE \
					% SGE_STRINGIZE(__LINE__) \
					% error_code_function(ret) \
					% message_str \
				) \
			);\
	}\
}; \
\
sge_error_sentry_ const sentry_instance_(\
	message \
);

#endif
