#include <sge/camera/projection/perspective.hpp>

sge::camera::projection::perspective::perspective(
	renderer::scalar const _aspect,
	renderer::scalar const _fov,
	renderer::scalar const _near,
	renderer::scalar const _far)
:
	aspect_(
		_aspect),
	fov_(
		_fov),
	near_(
		_near),
	far_(
		_far)
{
}

sge::renderer::scalar 
sge::camera::projection::perspective::aspect() const
{
	return aspect_;
}

sge::renderer::scalar 
sge::camera::projection::perspective::fov() const
{
	return fov_;
}

sge::renderer::scalar 
sge::camera::projection::perspective::near() const
{
	return near_;
}

sge::renderer::scalar 
sge::camera::projection::perspective::far() const
{
	return far_;
}
