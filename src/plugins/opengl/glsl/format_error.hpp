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


#ifndef SGE_OPENGL_GLSL_FORMAT_ERROR_HPP_INCLUDED
#define SGE_OPENGL_GLSL_FORMAT_ERROR_HPP_INCLUDED

#include <sge/container/raw_vector_impl.hpp>
#include <sge/string.hpp>
#include <sge/iconv.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{

template<
	typename Function,
	typename Id
>
fcppt::string const
format_error(
	Function const &function,
	Id const &id
)
{
	typedef container::raw_vector<
		char
	> errorlog_array;

	errorlog_array errorlog;

	errorlog.reserve(
		1024
	);

	GLint len;

	for(;;)
	{
		function(
			id,
			static_cast<
				GLint
			>(
			errorlog.capacity()
			),
			&len,
			errorlog.data()
		);

		if(
			static_cast<
				errorlog_array::size_type
			>(
				len
			)
			> errorlog.size()
		)
		{
			errorlog.reserve(
				errorlog.capacity() * 2
			);

			continue;
		}

		errorlog.resize(
			static_cast<
				errorlog_array::size_type
			>(
				len
			)
		);

		errorlog.push_back(0);

		return sge::iconv(
			errorlog.data()
		);
	}
}


}
}
}

#endif
