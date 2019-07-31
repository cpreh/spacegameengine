//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CONST_RAW_POINTER_HPP_INCLUDED
#define SGE_RENDERER_CONST_RAW_POINTER_HPP_INCLUDED

#include <sge/renderer/raw_value.hpp>


namespace sge
{
namespace renderer
{

/**
\brief A pointer to const raw data

\ingroup sge_renderer

Creates a box with value type renderer::size_type.

\see sge::renderer::raw_value
*/
typedef sge::renderer::raw_value const *const_raw_pointer;

}
}

#endif
