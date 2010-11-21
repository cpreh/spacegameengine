#ifndef SGE_RENDERER_MATRIX4_HPP_INCLUDED
#define SGE_RENDERER_MATRIX4_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/math/matrix/static.hpp>

namespace sge
{
namespace renderer
{
typedef
fcppt::math::matrix::static_<scalar,4,4>::type
matrix4;
}
}

#endif
