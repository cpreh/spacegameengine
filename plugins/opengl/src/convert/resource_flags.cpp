//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/resource_flags.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <fcppt/container/bitfield/operators.hpp>


GLuint
sge::opengl::convert::resource_flags(
	sge::renderer::resource_flags_field const &_flags
)
{
	return
		static_cast<
			GLuint
		>(
			(_flags & sge::renderer::resource_flags::dynamic)
			?
				GL_DYNAMIC_DRAW
			:
				GL_STATIC_DRAW
		);
}
