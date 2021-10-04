//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EXTENSION_SUPPORTED_HPP_INCLUDED
#define SGE_OPENGL_EXTENSION_SUPPORTED_HPP_INCLUDED

#include <sge/opengl/extension_set.hpp>


namespace sge::opengl
{

template<
	typename Type
>
inline
bool
extension_supported(
	sge::opengl::extension_set<
		Type
	> const &_extensions,
	Type const &_value
)
{
	return
		_extensions.count(
			_value
		)
		!=
		0U;
}

}

#endif
