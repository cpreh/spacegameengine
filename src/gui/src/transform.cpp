#include "../transform.hpp"
#include "../../renderer/transform.hpp"

sge::pos3 sge::gui::gui_to_space(const point p)
{
	return space_2d_to_3d(p);
}

sge::pos3 sge::gui::gui_to_space(const unit x, const unit y)
{
	return gui_to_space(point(x,y));
}
