//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_INFO_EXTENSION_SET_HPP_INCLUDED
#define SGE_OPENGL_INFO_EXTENSION_SET_HPP_INCLUDED

#include <sge/opengl/extension_set.hpp>
#include <sge/opengl/info/extension.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/strong_typedef_std_hash.hpp> // IWYU pragma: keep

namespace sge::opengl::info
{

using extension_set = sge::opengl::extension_set<sge::opengl::info::extension>;

}

#endif
