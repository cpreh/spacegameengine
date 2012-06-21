#ifndef SGE_OPENCL_EVENT_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_EVENT_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/event/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opencl
{
namespace event
{
typedef
boost::ptr_vector<sge::opencl::event::object>
sequence;
}
}
}

#endif

