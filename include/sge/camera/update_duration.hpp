#ifndef SGE_CAMERA_UPDATE_DURATION_HPP_INCLUDED
#define SGE_CAMERA_UPDATE_DURATION_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace camera
{
typedef
boost::chrono::duration<sge::renderer::scalar>
update_duration;
}
}

#endif

