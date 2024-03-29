//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_RENDER_CONTEXT_CREATE_HPP_INCLUDED
#define SGE_OPENGL_RENDER_CONTEXT_CREATE_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/target/base_ref.hpp>
#include <fcppt/log/object_reference.hpp>

namespace sge::opengl::render_context
{

sge::renderer::context::ffp_unique_ptr create(
    fcppt::log::object_reference,
    sge::opengl::context::object_ref,
    sge::renderer::target::base_ref);

}

#endif
