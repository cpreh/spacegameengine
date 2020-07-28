//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/get_string.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


std::string
sge::opengl::get_string(
	GLenum const _what
)
{
	GLubyte const *const ret(
		sge::opengl::call(
			::glGetString,
			_what
		)
	);

	if(
		ret
		==
		nullptr
	)
	{
		throw
			sge::renderer::exception(
				FCPPT_TEXT("glGetString() failed!")
			);
	}

	return
		std::string(
			fcppt::cast::to_char_ptr<
				char const *
			>(
				ret
			)
		);
}
