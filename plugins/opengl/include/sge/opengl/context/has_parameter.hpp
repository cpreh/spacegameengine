//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONTEXT_HAS_PARAMETER_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_HAS_PARAMETER_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::context
{

template<
	typename Type
>
using has_parameter
=
std::negation<
	std::is_same<
		typename Type::parameter,
		void
	>
>;

}

#endif
