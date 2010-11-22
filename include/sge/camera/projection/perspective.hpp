#ifndef SGE_CAMERA_PROJECTION_PERSPECTIVE_HPP_INCLUDED
#define SGE_CAMERA_PROJECTION_PERSPECTIVE_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
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
	SGE_CAMERA_SYMBOL
	explicit
	perspective(
		renderer::scalar aspect,
		renderer::scalar fov,
		renderer::scalar near,
		renderer::scalar far);

	SGE_CAMERA_SYMBOL
	renderer::scalar 
	aspect() const;

	SGE_CAMERA_SYMBOL
	renderer::scalar 
	fov() const;

	SGE_CAMERA_SYMBOL
	renderer::scalar 
	near() const;

	SGE_CAMERA_SYMBOL
	renderer::scalar 
	far() const;
private:
	renderer::scalar aspect_,fov_,near_,far_;
};
}
}
}

#endif
