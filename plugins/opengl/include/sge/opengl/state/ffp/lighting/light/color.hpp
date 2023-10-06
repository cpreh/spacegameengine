//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_FFP_LIGHTING_LIGHT_COLOR_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_LIGHTING_LIGHT_COLOR_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/opengl/state/index_actor.hpp>

namespace sge::opengl::state::ffp::lighting::light
{

sge::opengl::state::index_actor color(GLenum name, sge::image::color::any::object const &);

}

#endif
