//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_VARIANT_FWD_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_VARIANT_FWD_HPP_INCLUDED

#include <sge/renderer/state/ffp/lighting/light/directional_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/point_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace lighting
{
namespace light
{

typedef
fcppt::variant::object<
	sge::renderer::state::ffp::lighting::light::directional,
	sge::renderer::state::ffp::lighting::light::point,
	sge::renderer::state::ffp::lighting::light::spot
>
variant;

}
}
}
}
}
}

#endif
