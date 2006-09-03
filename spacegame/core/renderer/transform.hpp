#ifndef SGE_TRANSFORM_HPP_INCLUDED
#define SGE_TRANSFORM_HPP_INCLUDED

#include "../main/types.hpp"
#include "./renderer_types.hpp"

namespace sge
{

inline space_unit space_x_2d_to_3d(const space_unit x)
{
	return x*space_unit(2)-1;
}

inline space_unit space_y_2d_to_3d(const space_unit y)
{
	return -y*2+1;
}

inline pos3 space_2d_to_3d(const space_unit x, const space_unit y)
{
	return pos3(space_x_2d_to_3d(x),space_y_2d_to_3d(y),0);
}

inline pos3 space_2d_to_3d(const point pos)
{
	return space_2d_to_3d(pos.x,pos.y);
}

inline pos3 text_to_space(const space_unit x, const space_unit y)
{
	return space_2d_to_3d(x,y);
}

inline pos3 text_to_space(const point pos)
{
	return space_2d_to_3d(pos);
}

inline vector2<unsigned> space_pos_to_pixel(const point a, const unsigned screen_width, const unsigned screen_height)
{
	return vector2<unsigned>(unsigned((a.x + 1.0) / 2.0 * screen_width),
	                         unsigned((-a.y + 1.0) / 2.0 * screen_height));
}

inline unsigned space_size_to_pixel(const space_unit s, const unsigned screen_size)
{
	return unsigned((s / space_unit(2))) * screen_size;
}

inline space_unit pixel_size_to_space(const unsigned v, const unsigned screen_size)
{
	return space_unit(v * space_unit(2) / screen_size);
}

inline basic_rect<space_unit> space_rect_2d_to_3d(const basic_rect<space_unit>& r)
{
	return basic_rect<space_unit>(space_x_2d_to_3d(r.left), space_y_2d_to_3d(r.top),
	                              space_x_2d_to_3d(r.right), space_y_2d_to_3d(r.bottom));
}

}

#endif
