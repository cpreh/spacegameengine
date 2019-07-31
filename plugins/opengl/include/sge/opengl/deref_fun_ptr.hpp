//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_DEREF_FUN_PTR_HPP_INCLUDED
#define SGE_OPENGL_DEREF_FUN_PTR_HPP_INCLUDED

#include <sge/opengl/fun_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/assert/pre.hpp>


namespace sge
{
namespace opengl
{

template<
	typename Function
>
sge::opengl::fun_ref<
	Function
>
deref_fun_ptr(
	Function const _function
)
{
	FCPPT_ASSERT_PRE(
		_function
		!=
		nullptr
	);

	return
		fcppt::make_ref(
			*_function
		);

}

}
}

#endif
