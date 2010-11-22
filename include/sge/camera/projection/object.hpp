#ifndef SGE_CAMERA_PROJECTION_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_PROJECTION_OBJECT_HPP_INCLUDED

#include <sge/camera/projection/orthogonal.hpp>
#include <sge/camera/projection/perspective.hpp>
#include <fcppt/variant/object_decl.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace camera
{
namespace projection
{
typedef
fcppt::variant::object
<
	boost::mpl::vector2
	<
		orthogonal,
		perspective
	>
>
object;
}
}
}

#endif
