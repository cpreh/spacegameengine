//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_RASTERIZER_CULL_MODE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_RASTERIZER_CULL_MODE_HPP_INCLUDED

#include <sge/renderer/state/core/rasterizer/cull_mode_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace rasterizer
{

enum class cull_mode
{
	off,
	clockwise,
	counter_clockwise
};

}
}
}
}
}

#endif
