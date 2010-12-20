#ifndef SGE_SHADER_OBJECT_PTR_HPP_INCLUDED
#define SGE_SHADER_OBJECT_PTR_HPP_INCLUDED

#include <sge/shader/object_fwd.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sge
{
namespace shader
{
typedef
fcppt::shared_ptr<object>
object_ptr;
}
}

#endif
