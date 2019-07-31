//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_BLEND_ALPHA_ENABLED_FWD_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_ALPHA_ENABLED_FWD_HPP_INCLUDED

#include <sge/renderer/state/core/blend/combined_fwd.hpp>
#include <sge/renderer/state/core/blend/separate_fwd.hpp>
#include <fcppt/variant/variadic_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace blend
{

typedef
fcppt::variant::variadic<
	sge::renderer::state::core::blend::combined,
	sge::renderer::state::core::blend::separate
>
alpha_enabled;

}
}
}
}
}

#endif
