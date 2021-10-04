//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_OPTIONAL_CONFIG_FWD_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_OPTIONAL_CONFIG_FWD_HPP_INCLUDED

#include <sge/opengl/state/core/depth_stencil/stencil/config_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge::opengl::state::core::depth_stencil::stencil
{

using
optional_config
=
fcppt::optional::object<
	sge::opengl::state::core::depth_stencil::stencil::config
>;

}

#endif
