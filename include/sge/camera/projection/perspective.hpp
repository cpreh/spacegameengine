#ifndef SGE_CAMERA_PROJECTION_PERSPECTIVE_HPP_INCLUDED
#define SGE_CAMERA_PROJECTION_PERSPECTIVE_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>

namespace sge
{
namespace camera
{
namespace projection
{
class perspective
{
public:
	explicit
	perspective(
		renderer::scalar aspect,
		renderer::scalar fov,
		renderer::scalar near,
		renderer::scalar far);

	renderer::scalar 
	aspect() const;

	renderer::scalar 
	fov() const;

	renderer::scalar 
	near() const;

	renderer::scalar 
	far() const;
private:
	renderer::scalar aspect_,fov_,near_,far_;
};
}
}
}

#endif
