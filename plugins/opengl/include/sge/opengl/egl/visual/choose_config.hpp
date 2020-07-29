//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_VISUAL_CHOOSE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_EGL_VISUAL_CHOOSE_CONFIG_HPP_INCLUDED

#include <sge/opengl/egl/attribute_vector.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{
namespace visual
{

EGLConfig
choose_config(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	EGLDisplay,
	sge::opengl::egl::attribute_vector const &
);

}
}
}
}

#endif
