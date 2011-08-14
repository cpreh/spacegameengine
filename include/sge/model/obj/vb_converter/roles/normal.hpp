#ifndef SGE_MODEL_OBJ_VB_CONVERTER_ROLES_NORMAL_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_ROLES_NORMAL_HPP_INCLUDED

#include <sge/model/obj/vb_converter/roles/detail/type.hpp>
#include <boost/mpl/integral_c.hpp>

namespace sge
{
namespace model
{
namespace obj
{
namespace vb_converter
{
namespace roles
{
typedef
boost::mpl::integral_c
<
	detail::type,
	detail::normal
>
normal;
}
}
}
}
}

#endif
