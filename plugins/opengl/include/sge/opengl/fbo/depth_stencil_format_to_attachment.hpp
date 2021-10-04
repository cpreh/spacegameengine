//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_DEPTH_STENCIL_FORMAT_TO_ATTACHMENT_HPP_INCLUDED
#define SGE_OPENGL_FBO_DEPTH_STENCIL_FORMAT_TO_ATTACHMENT_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>


namespace sge::opengl::fbo
{

sge::opengl::fbo::optional_attachment_type
depth_stencil_format_to_attachment(
	sge::opengl::fbo::config const &,
	sge::image::ds::format
);

}

#endif
