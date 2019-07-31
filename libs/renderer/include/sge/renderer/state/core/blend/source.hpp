//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_BLEND_SOURCE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_SOURCE_HPP_INCLUDED

#include <sge/renderer/state/core/blend/source_fwd.hpp>


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

enum class source
{
	zero,
	one,
	dest_color,
	inv_dest_color,
	src_alpha,
	inv_src_alpha,
	dest_alpha,
	inv_dest_alpha,
	src_alpha_sat
};

}
}
}
}
}

#endif
