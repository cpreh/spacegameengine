#ifndef SGE_GUI_TYPES_HPP_INCLUDED
#define SGE_GUI_TYPES_HPP_INCLUDED

#include "../sprite/types.hpp"
#include "../sprite/fwd.hpp"
#include "../math/vector.hpp"
#include "../input/key_type.hpp"
#include "../input/key_state.hpp"
#include "../renderer/texture.hpp"
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
}
}

#endif
