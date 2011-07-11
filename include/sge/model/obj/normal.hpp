#ifndef SGE_MODEL_OBJ_NORMAL_HPP_INCLUDED
#define SGE_MODEL_OBJ_NORMAL_HPP_INCLUDED

#include <sge/model/obj/scalar.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sge
{
namespace model
{
namespace obj
{
typedef
fcppt::math::vector::static_<obj::scalar,3>::type
normal;
}
}
}

#endif
