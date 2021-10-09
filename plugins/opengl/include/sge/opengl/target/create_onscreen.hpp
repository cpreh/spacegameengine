//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TARGET_CREATE_ONSCREEN_HPP_INCLUDED
#define SGE_OPENGL_TARGET_CREATE_ONSCREEN_HPP_INCLUDED

#include <sge/opengl/backend/current_ref.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/renderer/target/onscreen_unique_ptr.hpp>
#include <awl/window/object_ref.hpp>

namespace sge::opengl::target
{

sge::renderer::target::onscreen_unique_ptr create_onscreen(
    sge::opengl::context::object_ref, sge::opengl::backend::current_ref, awl::window::object_ref);

}

#endif
