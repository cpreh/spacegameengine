#ifndef SGE_SCENIC_GRID_RECT_HPP_INCLUDED
#define SGE_SCENIC_GRID_RECT_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/math/box/object_fwd.hpp>

namespace sge
{
namespace scenic
{
namespace grid
{
typedef
fcppt::math::box::object<sge::renderer::scalar,2>
rect;
}
}
}

#endif
