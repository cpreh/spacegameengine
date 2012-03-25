#ifndef SGE_CAMERA_FIRST_PERSON_ACTION_WASD_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_ACTION_WASD_MAPPING_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/first_person/action/mapping.hpp>


namespace sge
{
namespace camera
{
namespace first_person
{
namespace action
{
/**
\brief Creates a typical 'w','a','s','d' ego-shooter key mapping
\ingroup sgecamera

Up and down are mapped to space and left ctrl, respectively.
*/
SGE_CAMERA_SYMBOL
action::mapping const
wasd_mapping();
}
}
}
}

#endif

