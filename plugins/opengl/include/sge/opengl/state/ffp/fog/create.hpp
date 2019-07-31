//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_FOG_CREATE_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_FOG_CREATE_HPP_INCLUDED

#include <sge/renderer/state/ffp/fog/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/fog/parameters_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace fog
{

sge::renderer::state::ffp::fog::object_unique_ptr
create(
	sge::renderer::state::ffp::fog::parameters const &
);

}
}
}
}
}

#endif
