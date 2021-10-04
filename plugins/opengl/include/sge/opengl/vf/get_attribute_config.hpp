//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_GET_ATTRIBUTE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_VF_GET_ATTRIBUTE_CONFIG_HPP_INCLUDED

#include <sge/opengl/vf/attribute_config_fwd.hpp>
#include <sge/opengl/vf/attribute_context_fwd.hpp>


namespace sge::opengl::vf
{

sge::opengl::vf::attribute_config const &
get_attribute_config(
	sge::opengl::vf::attribute_context const &
);

}

#endif
