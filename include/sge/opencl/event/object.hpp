#ifndef SGE_OPENCL_EVENT_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_EVENT_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opencl
{
namespace event
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL
	object();

	SGE_OPENCL_SYMBOL
	cl_event &
	handle();

	SGE_OPENCL_SYMBOL
	cl_event const &
	handle() const;

	SGE_OPENCL_SYMBOL
	~object();
private:
	cl_event handle_;
	mutable bool handle_retrieved_;
};
}
}
}

#endif

