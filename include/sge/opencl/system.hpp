#ifndef SGE_OPENCL_SYSTEM_HPP_INCLUDED
#define SGE_OPENCL_SYSTEM_HPP_INCLUDED

#include <sge/opencl/platform/object_sequence.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/platform/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opencl
{
class system
{
FCPPT_NONCOPYABLE(
	system);
public:
	SGE_OPENCL_SYMBOL explicit
	system();

	SGE_OPENCL_SYMBOL opencl::platform::object_sequence &
	platforms();

	SGE_OPENCL_SYMBOL opencl::platform::object_sequence const &
	platforms() const;

	SGE_OPENCL_SYMBOL ~system();
private:
	opencl::platform::object_sequence platforms_;
};
}
}

#endif
