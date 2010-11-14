#ifndef SGE_SHADER_VEC4_HPP_INCLUDED
#define SGE_SHADER_VEC4_HPP_INCLUDED

#include <sge/shader/scalar.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sge
{
namespace shader
{
typedef
fcppt::math::vector::static_<scalar,4>::type
vec4;
}
}

#endif
