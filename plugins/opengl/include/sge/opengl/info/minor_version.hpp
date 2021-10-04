//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_INFO_MINOR_VERSION_HPP_INCLUDED
#define SGE_OPENGL_INFO_MINOR_VERSION_HPP_INCLUDED

#include <sge/opengl/info/version_type.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge::opengl::info
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::opengl::info::version_type,
	minor_version
);

}

#endif
