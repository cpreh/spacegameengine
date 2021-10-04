//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CALL_FUN_REF_HPP_INCLUDED
#define SGE_OPENGL_CALL_FUN_REF_HPP_INCLUDED

#include <sge/opengl/apientry.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::opengl
{

template<
	typename Result,
	typename... Args
>
inline
Result
call_fun_ref(
	fcppt::reference<
		Result SGE_OPENGL_APIENTRY (Args...)
	> const _fun,
	Args... _args
)
{
	return
		_fun.get()(
			_args...
		);
}

}

#endif
