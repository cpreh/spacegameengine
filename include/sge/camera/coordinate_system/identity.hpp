#ifndef SGE_CAMERA_COORDINATE_SYSTEM_IDENTITY_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_IDENTITY_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/coordinate_system/object_fwd.hpp>

namespace sge
{
namespace camera
{
namespace coordinate_system
{
/**
\brief Returns the canonical coordinate system
\ingroup sgecamera

This sets right to (1,0,0), up to (0,1,0), forward to (0,0,1) and position to
the origin. Classes like sge::camera::first_person::parameters use this
coordinate system as a sensible default.
*/
SGE_CAMERA_SYMBOL
coordinate_system::object const
identity();
}
}
}

#endif

