//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>


sge::opengl::context::id
sge::opengl::context::make_id()
noexcept
{
	static
	sge::opengl::context::id::type counter{
		0U
	};

	return
		sge::opengl::context::id{
			++counter
		};
}
