#ifndef SGE_GUI_TYPES_HPP_INCLUDED
#define SGE_GUI_TYPES_HPP_INCLUDED

#include "../sprite/unit.hpp"
#include "../sprite/point.hpp"
#include "../sprite/dim.hpp"
#include "../sprite/rect.hpp"
#include "../sprite/fwd.hpp"
#include "../math/vector.hpp"
#include "../math/rect.hpp"
#include "../input/key_type.hpp"
#include "../input/key_state.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/image_view.hpp"
#include "../renderer/image.hpp"
#include "../renderer/any_color.hpp"

namespace sge
{
namespace gui
{
typedef sprite::unit unit;
typedef sprite::point point;
typedef sprite::dim dim;
typedef sprite::rect rect;
typedef math::vector<input::key_state,2u> mouse_point;

namespace direction
{
enum type { up,down,left,right };
}

typedef renderer::any_color color;
typedef renderer::rgba8_color internal_color;

typedef renderer::image_view image_view;
typedef renderer::const_image_view const_image_view;

typedef renderer::rgba8_image image;
}
}

#endif
