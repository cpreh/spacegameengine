//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_RENDER_CONTEXT_CREATE_HPP_INCLUDED
#define SGE_OPENGL_RENDER_CONTEXT_CREATE_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace render_context
{

sge::renderer::context::ffp_unique_ptr
create(
	fcppt::log::object &,
	sge::opengl::context::object &,
	sge::renderer::target::base &
);

}
}
}

#endif
