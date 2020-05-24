//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_VARIANT_FWD_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_VARIANT_FWD_HPP_INCLUDED

#include <sge/renderer/state/core/depth_stencil/stencil/enabled_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace depth_stencil
{
namespace stencil
{

using
variant
=
fcppt::variant::object<
	sge::renderer::state::core::depth_stencil::stencil::off,
	sge::renderer::state::core::depth_stencil::stencil::enabled
>;

}
}
}
}
}
}

#endif
