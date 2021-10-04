//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_FIRST_PERSON_ACTION_WASD_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_ACTION_WASD_MAPPING_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/first_person/action/mapping.hpp>


namespace sge::camera::first_person::action
{

/**
\brief Creates a typical 'w','a','s','d' ego-shooter key mapping
\ingroup sgecamera

Up and down are mapped to space and left ctrl, respectively.
*/
SGE_CAMERA_DETAIL_SYMBOL
sge::camera::first_person::action::mapping
wasd_mapping();

}

#endif
