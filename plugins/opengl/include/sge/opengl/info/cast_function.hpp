//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_INFO_CAST_FUNCTION_HPP_INCLUDED
#define SGE_OPENGL_INFO_CAST_FUNCTION_HPP_INCLUDED

#include <sge/opengl/backend/fun_ptr.hpp>


namespace sge
{
namespace opengl
{
namespace info
{

template<
	typename Ret
>
Ret
cast_function(
	sge::opengl::backend::fun_ptr const _function
)
{
	return
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		reinterpret_cast<
			Ret
		>(
			_function
		);
}

}
}
}

#endif
