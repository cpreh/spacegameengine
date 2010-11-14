#ifndef SGE_SHADER_MAT4_HPP_INCLUDED
#define SGE_SHADER_MAT4_HPP_INCLUDED

#include <sge/shader/scalar.hpp>
#include <fcppt/math/matrix/static.hpp>

namespace sge
{
namespace shader
{
typedef
fcppt::math::matrix::static_
<
	scalar,
	4,
	4
>::type
mat4;
}
}

#endif
