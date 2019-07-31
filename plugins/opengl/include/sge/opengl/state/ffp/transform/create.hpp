//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_TRANSFORM_CREATE_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_TRANSFORM_CREATE_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace transform
{

sge::renderer::state::ffp::transform::object_unique_ptr
create(
	sge::opengl::context::object &,
	sge::renderer::state::ffp::transform::parameters const &
);

}
}
}
}
}

#endif
