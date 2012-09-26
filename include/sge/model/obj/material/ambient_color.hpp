#ifndef SGE_MODEL_OBJ_MATERIAL_AMBIENT_COLOR_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_AMBIENT_COLOR_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace model
{
namespace obj
{
namespace material
{
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::image::color::any::object,
	ambient_color);
}
}
}
}

#endif
