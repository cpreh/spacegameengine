//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_ORTHO_FREELOOK_ACTION_WSG_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_ACTION_WSG_MAPPING_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/ortho_freelook/action/mapping.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{
namespace action
{

/**
\brief Creates mapping where 'w' and 's' zoom in/out and 'g' activates the panning.
\ingroup sgecamera
*/
SGE_CAMERA_DETAIL_SYMBOL
sge::camera::ortho_freelook::action::mapping
wsg_mapping();

}
}
}
}

#endif
