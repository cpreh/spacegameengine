//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_SYSTEM_HPP_INCLUDED
#define SGE_OPENCL_SYSTEM_HPP_INCLUDED

#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/platform/object_sequence.hpp>
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
	SGE_OPENCL_DETAIL_SYMBOL explicit
	system();

	SGE_OPENCL_DETAIL_SYMBOL opencl::platform::object_sequence &
	platforms();

	SGE_OPENCL_DETAIL_SYMBOL opencl::platform::object_sequence const &
	platforms() const;

	SGE_OPENCL_DETAIL_SYMBOL ~system();
private:
	opencl::platform::object_sequence platforms_;
};
}
}

#endif
