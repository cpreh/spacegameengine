//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FUN_REF_HPP_INCLUDED
#define SGE_OPENGL_FUN_REF_HPP_INCLUDED

#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl
{

template<
	typename Type
>
using
fun_ref
=
fcppt::reference<
	std::remove_pointer_t<
		Type
	>
>;

}

#endif
