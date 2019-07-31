//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_NORMAL_LOCK_METHOD_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_NORMAL_LOCK_METHOD_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

GLenum
normal_lock_method(
	sge::renderer::lock_flags::method
);

}
}
}

#endif
