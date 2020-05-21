//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CLEAR_DEPTH_BUFFER_VALUE_HPP_INCLUDED
#define SGE_RENDERER_CLEAR_DEPTH_BUFFER_VALUE_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>


namespace sge
{
namespace renderer
{
namespace clear
{

/**
\brief The depth buffer clear type

\ingroup sge_renderer

Depth buffers are cleared using scalars in [0,1].
*/
using
depth_buffer_value
=
sge::renderer::scalar;

}
}
}

#endif
