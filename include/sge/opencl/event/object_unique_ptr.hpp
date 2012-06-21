#ifndef SGE_OPENCL_EVENT_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SGE_OPENCL_EVENT_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sge/opencl/event/object_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sge
{
namespace opencl
{
namespace event
{
typedef
fcppt::unique_ptr<sge::opencl::event::object>
object_unique_ptr;
}
}
}

#endif

