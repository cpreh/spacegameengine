//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_OPTIONAL_HARDWARE_CONFIG_FWD_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_OPTIONAL_HARDWARE_CONFIG_FWD_HPP_INCLUDED

#include <sge/opengl/buffer/hardware_config_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge::opengl::buffer
{

using
optional_hardware_config
=
fcppt::optional::object<
	sge::opengl::buffer::hardware_config
>;

}

#endif
