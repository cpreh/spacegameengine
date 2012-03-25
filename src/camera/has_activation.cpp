#include <sge/camera/has_activation.hpp>

sge::camera::has_activation::has_activation()
{
}

void
sge::camera::has_activation::toggle_is_active()
{
	this->is_active(
		!this->is_active());
}

sge::camera::has_activation::~has_activation()
{
}
