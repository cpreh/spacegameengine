//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_TRANSFORM_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_TRANSFORM_ACTOR_HPP_INCLUDED

#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>
#include <fcppt/function_impl.hpp>


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

using
actor
=
fcppt::function<
	void(
		sge::renderer::state::ffp::transform::mode const &
	)
>;

}
}
}
}
}

#endif
