//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_CONST_OBJECT_REF_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_CONST_OBJECT_REF_HPP_INCLUDED

#include <sge/renderer/state/ffp/lighting/light/object_fwd.hpp>
#include <fcppt/reference.hpp>


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

using
const_object_ref
=
fcppt::reference<
	sge::renderer::state::ffp::lighting::light::object const
>;

}
}
}
}
}
}

#endif
