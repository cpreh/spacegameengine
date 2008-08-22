#ifndef SGE_GUI_TYPES_HPP_INCLUDED
#define SGE_GUI_TYPES_HPP_INCLUDED

#include <sge/sprite/types.hpp>
#include <sge/sprite/fwd.hpp>
#include <sge/math/vector.hpp>
#include <sge/input/key_type.hpp>
#include <sge/renderer/texture.hpp>

namespace sge
{
namespace gui
{
typedef sprite::unit unit;
typedef sprite::point point;
typedef sprite::dim dim;
typedef sprite::rect rect;
typedef math::basic_vector<input::key_state,2u> mouse_point;

namespace direction
{
enum type { up,down,left,right };
}
}
}

#endif
