//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CLEAR_BACK_BUFFER_VALUE_FWD_HPP_INCLUDED
#define SGE_RENDERER_CLEAR_BACK_BUFFER_VALUE_FWD_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace clear
{

/**
\brief The type used for backbuffer clearing

\ingroup sge_renderer

Backbuffers are cleared using any color.
*/
using
back_buffer_value
=
sge::image::color::any::object;

}
}
}

#endif
