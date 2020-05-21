//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_RAW_POINTER_HPP_INCLUDED
#define SGE_RENDERER_RAW_POINTER_HPP_INCLUDED

#include <sge/renderer/raw_value.hpp>


namespace sge
{
namespace renderer
{

/**
\brief A pointer to raw data

\ingroup sge_renderer

\see sge::renderer::raw_value
*/
using
raw_pointer
=
sge::renderer::raw_value *;

}
}

#endif
