//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/range_lock_method.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::buffer::range_lock_method(
	sge::renderer::lock_flags::method const _method
)
{
	switch(
		_method
	)
	{
	case sge::renderer::lock_flags::method::read:
		return
			GL_MAP_READ_BIT;
	case sge::renderer::lock_flags::method::write:
		return
			GL_MAP_WRITE_BIT // NOLINT(hicpp-signed-bitwise)
			|
			GL_MAP_INVALIDATE_RANGE_BIT;
	case sge::renderer::lock_flags::method::readwrite:
		return
			GL_MAP_READ_BIT // NOLINT(hicpp-signed-bitwise)
			|
			GL_MAP_WRITE_BIT;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
