//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EXTENSION_SET_HPP_INCLUDED
#define SGE_OPENGL_EXTENSION_SET_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl
{

template<
	typename Type
>
using
extension_set
=
std::unordered_set<
	Type
>;

}

#endif
