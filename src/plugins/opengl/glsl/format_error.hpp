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
	typename Id,
	typename Context
>
fcppt::string const
format_error(
	Function const &function_,
	LengthFunction const &length_function_,
	Id const &id_,
	Context const &context_
)
{
	typedef fcppt::container::raw_vector<
		char
	> errorlog_array;

	GLint const required_length(
		length_function_(
			context_,
			id_
		)
	);

	if(
		required_length == 0
	)
		return fcppt::string(
			FCPPT_TEXT("glsl::format_error: No message.")
		);

	// note: required_length includes the terminating 0 character,
	// so we should get at least 1
	FCPPT_ASSERT(
		required_length > 0
	);

	errorlog_array errorlog(
		static_cast<
			errorlog_array::size_type
		>(
			required_length
		)
	);

	GLsizei length_return;

	function_(
		context_,
		id_,
		static_cast<
			GLint
		>(
			errorlog.size()
		),
		&length_return,
		errorlog.data()
	);

	// note: the required length includes the terminating 0 character,
	// while length_return does not!
	FCPPT_ASSERT(
		length_return
		==
		static_cast<
			GLsizei
		>(
			required_length - 1
		)
	);

	return
		fcppt::from_std_string(
			errorlog.data()
		);
}

}
}
}

#endif
