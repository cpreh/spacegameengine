//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_FFP_TRANSFORM_SET_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_TRANSFORM_SET_HPP_INCLUDED

#include <sge/d3d9/state/ffp/transform/object_fwd.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace transform
{

void set(
    sge::renderer::state::ffp::transform::mode,
    sge::renderer::state::ffp::transform::const_optional_object_ref const &,
    sge::d3d9::state::ffp::transform::object const &);

}
}
}
}
}

#endif
