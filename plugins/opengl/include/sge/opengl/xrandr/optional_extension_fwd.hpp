//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_OPTIONAL_EXTENSION_FWD_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_OPTIONAL_EXTENSION_FWD_HPP_INCLUDED

#include <sge/opengl/xrandr/extension_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

using
optional_extension
=
fcppt::optional::object<
	sge::opengl::xrandr::extension
>;

}
}
}

#endif
