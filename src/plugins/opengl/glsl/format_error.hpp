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

#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/from_std_string.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{

template<
	typename Function,
	typename LengthFunction,
	typename Id
>
fcppt::string const
format_error(
	Function const &function,
	LengthFunction const &length_function,
	Id const &id
)
{
	typedef fcppt::container::raw_vector<
		char
	> errorlog_array;

	GLint const required_length(
		length_function(
			id
		)
	);

	if(
		required_length <= 0
	)
		return fcppt::string(
			FCPPT_TEXT("glsl::format_error: No message.")
		);

	errorlog_array errorlog(
		static_cast<
			errorlog_array::size_type
		>(
			required_length
		)
	);

	GLsizei length_return;

	function(
		id,
		static_cast<
			GLint
		>(
			errorlog.size()
		),
		&length_return,
		errorlog.data()
	);

	FCPPT_ASSERT(
		length_return
		==
		static_cast<
			GLsizei
		>(
			required_length
		)
	);

	return fcppt::from_std_string(
		errorlog.data()
	);
}

}
}
}

#endif
