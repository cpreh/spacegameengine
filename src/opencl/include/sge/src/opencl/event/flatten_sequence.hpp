#ifndef SGE_SRC_OPENCL_EVENT_FLATTEN_SEQUENCE_HPP_INCLUDED
#define SGE_SRC_OPENCL_EVENT_FLATTEN_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/event/sequence.hpp>
#include <fcppt/container/raw_vector.hpp>


namespace sge
{
namespace opencl
{
namespace event
{
fcppt::container::raw_vector<cl_event> const
flatten_sequence(
	sge::opencl::event::sequence const &);
}
}
}

#endif

