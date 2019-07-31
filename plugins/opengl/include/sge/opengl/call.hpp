//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CALL_HPP_INCLUDED
#define SGE_OPENGL_CALL_HPP_INCLUDED

#include <sge/opengl/apientry.hpp>


namespace sge
{
namespace opengl
{

template<
	typename Result,
	typename... Args
>
inline
Result
call(
	Result (SGE_OPENGL_APIENTRY &_fun)(Args...),
	Args... _args
)
{
	return
		_fun(
			_args...
		);
}

}
}

#endif
