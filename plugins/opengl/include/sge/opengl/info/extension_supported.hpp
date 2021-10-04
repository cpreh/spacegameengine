//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_INFO_EXTENSION_SUPPORTED_HPP_INCLUDED
#define SGE_OPENGL_INFO_EXTENSION_SUPPORTED_HPP_INCLUDED

#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_set.hpp>


namespace sge::opengl::info
{

bool
extension_supported(
	sge::opengl::info::extension_set const &,
	sge::opengl::info::extension const &
);

}

#endif
